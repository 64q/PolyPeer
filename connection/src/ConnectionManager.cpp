#include <string>


#include <ConnectionManager.hpp>

ConnectionManager::ConnectionManager(WaitingPackets* waitingPackets):waitingPackets(waitingPackets)
{
	//ctor
}

ConnectionManager::~ConnectionManager()
{
	//dtor
}

void ConnectionManager::addConnection(std::string name, Socket* socket)
{

	Connection* tmp = new Connection(socket, waitingPackets);
	listConnections[name] = tmp;
	tmp->start();
}

Connection* ConnectionManager::getConnection(std::string name)
{
	return listConnections[name];
}


