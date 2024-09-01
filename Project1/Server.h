#pragma once
#pragma once

#include <WinSock2.h>
#include <Windows.h>
// #include "Helper.h"
#include <algorithm>
#include <mutex>
#include <string>
// #include <>
#include <condition_variable>



class Server
{
public:
	Server();
	~Server();
	void serve(int port);

private:

	void acceptClient();
	void clientHandler(SOCKET clientSocket);
	//// send msg from que
	//void sendMsgFromQue();
	//// get the right name of a file
	//std::string getFileName(std::string myName, std::string otherName);

	SOCKET _serverSocket;
};

