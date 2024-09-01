#pragma once


#include <WinSock2.h>
#include <Windows.h>
// #include "Helper.h"
#include <algorithm>
#include <mutex>
#include <string>
#include <map>
#include <condition_variable>
#include"IRequestHandler.h"


class Communicator
{
public:
	Communicator();
	~Communicator();
	void stratHandleRequest();

private:
	//methods
	void BindAndListen(int port);
	void handleNewClient(SOCKET clientSocket);

	//helper
	void acceptClient();

	// fields
	std::map<SOCKET, IRequestHandler*> _socketMap;
	SOCKET _serverSocket;
};



