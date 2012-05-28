// Class header
#include <BaseServer.hpp>

// STL
#include <iostream>


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

void BaseServer::multiSleep(int millisecond)
{
	 #ifdef WIN32
		Sleep(millisecond);
    #elif defined (linux)
		usleep(millisecond*1000);
    #endif
}

