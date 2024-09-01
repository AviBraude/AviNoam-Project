#include "Server.h"
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


Server::Server()
{

	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Server::~Server()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(_serverSocket);
	}
	catch (...) {}
}

void Server::serve(int port)
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

	//// creating one thread that will take care on msg que
	//std::thread msgHandler(&Server::sendMsgFromQue, this);
	//msgHandler.detach();

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		std::cout << "Waiting for client connection request" << std::endl;
		acceptClient();
	}
}


void Server::acceptClient()
{

	// this accepts the client and create a specific socket from server to this client
	// the process will not continue until a client connects to the server
	SOCKET client_socket = accept(_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted. Server and client can speak" << std::endl;
	// the function that handle the conversation with the client
	//thread* t = new thread;
	//t();
	//thread t;
	std::thread clientThread(&Server::clientHandler, this, client_socket);
	clientThread.detach();
}


void Server::clientHandler(SOCKET clientSocket)
{
	try
	{
		//std::string s = "Welcome! What is your name (4 bytes)? ";
		//send(clientSocket, s.c_str(), s.size(), 0);  // last parameter: flag. for us will be 0.
		/*string userName;
		char m[5];
		recv(clientSocket, m, 5, 0);
		int namelen = m[4] - '0';
		char* clientName = new char[namelen];
		recv(clientSocket, clientName , namelen, 0);
		std::string userName(clientName);

		//delete[] clientName;
		*/
		int namelen;
		string userName;
		string otherName;
		string fileName;
		int datalen;
		string data;
		string allUsersName;
		set<string> userFiles;
		fstream myFile;

		Helper::getIntPartFromSocket(clientSocket, 3);
		namelen = Helper::getIntPartFromSocket(clientSocket, 2);
		userName = Helper::getStringPartFromSocket(clientSocket, namelen);
		std::cout << "Client name is: " << userName << std::endl;

		socketByName[userName] = clientSocket;
		nameBySocket[clientSocket] = userName;
		Helper::send_update_message_to_client(clientSocket, data, userName, allUsersName);

		while (true)
		{
			// tear the msg apart
			Helper::getIntPartFromSocket(clientSocket, 3);
			namelen = Helper::getIntPartFromSocket(clientSocket, 2);
			otherName = Helper::getStringPartFromSocket(clientSocket, namelen);
			fileName = getFileName(userName, otherName);
			datalen = Helper::getIntPartFromSocket(clientSocket, 2);
			data = Helper::getStringPartFromSocket(clientSocket, datalen);

			if (data != "")
			{
				if (data == "exit")
					break;
				else
				{
					myFile.open(fileName, ios::app);
					myFile << '&' + data;
				}

			}
			map<string, SOCKET>::iterator it = socketByName.begin();

			// Iterate through the map and print the elements
			/*while (it != socketByName.end()) {
				allUsersName += it->first;
				++it;
			}*/
			for_each(socketByName.begin(), socketByName.end(), [&allUsersName](pair<string, SOCKET> p) {allUsersName += p.first + '&'; });

			//allUsersName = iterator(socketByName.begin(), socketByName.end(), );
			Helper::send_update_message_to_client(clientSocket, fileName, otherName, allUsersName);

		}
		/*char m[5];
		recv(clientSocket, m, 4, 0);
		m[4] = 0;
		std::cout << "Client name is: " << m << std::endl;*/

		// Closing the socket (in the level of the TCP protocol)
		std::string s = "Bye";
		send(clientSocket, s.c_str(), s.size(), 0);
		closesocket(clientSocket);
	}
	catch (const std::exception& e)
	{
		closesocket(clientSocket);
	}




//string Server::getFileName(string myName, string otherName)
//{
//	if (myName > otherName)
//		return otherName + '&' + myName;
//	return myName + '&' + otherName;
//}

