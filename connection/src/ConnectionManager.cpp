#include <string>


#include <ConnectionManager.hpp>

ConnectionManager::ConnectionManager(WaitingPackets* waitingPackets):waitingPackets(waitingPackets)
{
	serverSocket = new ServerSocket(5555);
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

void* runFct(void* connectionManager)
{
	ConnectionManager* connectionManagerTmp = (ConnectionManager*)connectionManager;
	connectionManagerTmp->run = true;
	Socket* sockTmp;
	while(connectionManagerTmp->run)
	{
		sockTmp = connectionManagerTmp->serverSocket->accept();
		connectionManagerTmp->addConnection(sockTmp->getIpAdress(), sockTmp);
		cout << "conect ajouté"<<endl;
	}
	return NULL;
}


void ConnectionManager::start()
{

	pthread_create(&thread, NULL, runFct, this);

}

void ConnectionManager::stop()
{
	run = false;

	std::map<std::string, Connection*>::const_iterator itr;
	for(itr = listConnections.begin(); itr!=listConnections.end(); ++itr)
	{
		delete itr->second;
	}

	serverSocket->close();
}



