#include "Server.h"
#include "Communicator.h"
#include "SqliteDatabase.h"

Server::Server()
{
	_database = new SQliteDatabase;
	_handleFactory = new RequestHandlerFactory(*_database);
	_Communicator = new Communicator(*_handleFactory);	
}
Server::~Server()
{
	delete _Communicator;
}
void Server::run(int port)
{
	_Communicator->stratHandleRequest(port);

}
