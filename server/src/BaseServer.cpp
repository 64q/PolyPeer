#include <iostream>

#include <BaseServer.hpp>

using namespace std;

BaseServer::BaseServer(const std::string logPath) :
	logger(logPath)
{

}

Logger& BaseServer::getLogger() 
{ 
	return this->logger; 
}

BaseServer::~BaseServer() {}
