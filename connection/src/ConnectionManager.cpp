#include <string>


#include <ConnectionManager.hpp>

ConnectionManager::ConnectionManager(std::vector<char*>* waitingMessage):waitingMessage(waitingMessage)
{
	//ctor
}

ConnectionManager::~ConnectionManager()
{
	//dtor
}

void ConnectionManager::addConnection(std::string name, Socket* socket)
{
	Connection* tmp = new Connection(socket, waitingMessage);
	listConnections[name] = tmp;
	tmp->start();
}

