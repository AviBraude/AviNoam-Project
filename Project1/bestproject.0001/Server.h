# pragma once
#include "Communicator.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"

class Server {
private:
	Communicator* _Communicator;
	IDatabase* _database;
	RequestHandlerFactory* _handleFactory;
public:
	Server();
	~Server();

	void run(int port);
};