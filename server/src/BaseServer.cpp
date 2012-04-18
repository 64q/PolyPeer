#include <iostream>

#include <BaseServer.hpp>

using namespace std;

BaseServer::BaseServer(const std::string logPath) :
	logger(logPath)
{

}

BaseServer::~BaseServer() {}
