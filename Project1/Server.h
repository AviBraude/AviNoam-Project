# pragma once
#include "Communicator.h"



class Server {
private:
	Communicator _Communicator;
public:
	void run();
};