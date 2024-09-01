#pragma comment (lib, "ws2_32.lib")

#include "WSAInitializer.h"
#include "Server.h"
#include <iostream>
#include <exception>

#include "sqlite3.h"


int main()
{
	try
	{
		WSAInitializer wsaInit;
		Server myServer;

		myServer.run(8820);
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	system("PAUSE");
	return 0;
}