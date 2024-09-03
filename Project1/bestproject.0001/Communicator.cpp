#include "Communicator.h"
//#include "messege.h"
#include <exception>
#include <iostream>
#include <string>
#include <thread>
#include <queue>
#include <vector>
#include <set>
#include "map"
#include <fstream>
#include "LoginRequestHandler.h"
#include <chrono>

Communicator::Communicator(RequestHandlerFactory& factory) : _factory(factory)
{

	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Communicator::~Communicator()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(_serverSocket);
	}
	catch (...) {}
}

void Communicator::stratHandleRequest(int port)
{
	this->BindAndListen(port);
	acceptClient();

}

int Communicator::fromBytsToInt(char* chai)
{
	int res = 0;
	res += chai[3];
	res += chai[2] * 256;
	res += chai[1] * 256 * 256;
	res += chai[0] * 256 * 256 *256;
	return res;
}

void Communicator::BindAndListen(int port)
{

	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = 0;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << port << std::endl;

}


void Communicator::acceptClient()
{

	while (true)
	{
		std::cout << "Waiting for client connection request" << std::endl;

		// this accepts the client and create a specific socket from server to this client
		// the process will not continue until a client connects to the server
		SOCKET client_socket = accept(_serverSocket, NULL, NULL);
		if (client_socket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);

		std::cout << "Client accepted. Server and client can speak" << std::endl;
		std::thread clientThread(&Communicator::handleNewClient, this, client_socket);
		clientThread.detach();
	}
}


void Communicator::handleNewClient(SOCKET clientSocket)
{
	_socketMap[clientSocket] = _factory.creatLoginRequestHandler();
	
	int byteFromSocket;
	char messegeCode;
	char lengthBuffer[4];
	RequestInfo reqInfo;

	while (true)
	{
		try
		{
			byteFromSocket = recv(clientSocket, &messegeCode, 1, 0);
			reqInfo._msgCode = int(messegeCode);

			byteFromSocket = recv(clientSocket, lengthBuffer, 4, 0);
			// make length buffer int ------------>>>>>>>>>>>>> have to check if that's OK
			int msgSize = fromBytsToInt(lengthBuffer);

			char* tmpMsgBuff = new char[msgSize];
			byteFromSocket = recv(clientSocket, tmpMsgBuff, msgSize, 0);
			for (int i = 0; i < msgSize; i++)
			{
				reqInfo._msgInfo.push_back(tmpMsgBuff[i]);
			}
			delete[] tmpMsgBuff;
			reqInfo._msgTime = std::chrono::system_clock::now();

			if (this->_socketMap[clientSocket]->isRequestRelevent(reqInfo))
			{
				RequestResult resy = this->_socketMap[clientSocket]->handleRequest(reqInfo);
				delete this->_socketMap[clientSocket];
				this->_socketMap[clientSocket] = resy.newHandler;

				std::string sendBuf = "";
				for (int i = 0; i < resy._msgBuffer.size(); i++)
				{
					sendBuf += resy._msgBuffer[i];
				}
				const char* sendChar = sendBuf.c_str();
				byteFromSocket = send(clientSocket, sendChar, sendBuf.size(), 0);
			}

			closesocket(clientSocket);
		}
		catch (const std::exception& e)
		{
			closesocket(clientSocket);
		}
	}
}



//string Server::getFileName(string myName, string otherName)
//{
//	if (myName > otherName)
//		return otherName + '&' + myName;
//	return myName + '&' + otherName;
//}

