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


Communicator::Communicator()
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

void Communicator::BindAndListen(int port)
{

	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << port << std::endl;
	std::thread acceptor(&Communicator::acceptClient, this);
	acceptor.detach();

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
	try
	{
		char m[6];

		recv(clientSocket, m, 5, 0);
		m[5] = 0;
		std::cout << m << std::endl;


		//std::cout << "here" << std::endl;
		std::string s = "Hello";
		send(clientSocket, s.c_str(), s.size(), 0);


		// Closing the socket (in the level of the TCP protocol)
		/*std::string s = "Bye";
		send(clientSocket, s.c_str(), s.size(), 0);*/

		closesocket(clientSocket);
	}
	catch (const std::exception& e)
	{
		closesocket(clientSocket);
	}
}



//string Server::getFileName(string myName, string otherName)
//{
//	if (myName > otherName)
//		return otherName + '&' + myName;
//	return myName + '&' + otherName;
//}

