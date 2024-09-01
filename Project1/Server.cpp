#include "Server.h"
#include "Communicator.h"
Server::Server()
{
	_Communicator = new Communicator;
}
Server::~Server()
{
	delete _Communicator;
}
void Server::run(int port)
{
	_Communicator->stratHandleRequest(port);

}
