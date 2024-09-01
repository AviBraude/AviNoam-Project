# pragma once
#include "Communicator.h"



class Server {
private:
	Communicator* _Communicator;
public:
	Server();
	~Server();

	void run(int port);
};