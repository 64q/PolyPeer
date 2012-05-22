#include <iostream>
#include <exception>
#include <map>

#include <Server.hpp>
#include <Entity.hpp>
#include <WebServer.hpp>
#include <Logger.hpp>
#include <Host.hpp>

using namespace std;

Server* Server::instance = NULL;

Server* Server::getInstance()
{
	if (instance == NULL)
	{
		instance = new Server();
	}
	
	return instance;
}

