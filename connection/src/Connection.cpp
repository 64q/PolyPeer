#include <Connection.hpp>

#include <iostream>
using namespace std;

Connection::Connection(Socket* socket, WaitingPackets* waitingPackets): socket(socket), waitingPackets(waitingPackets)
{
	//ctor
}

Connection::~Connection()
{
	stop();
}

void* listenSocket(void* connection)
{

	Connection* connectionTmp = (Connection*)connection;
	connectionTmp->run = true;
	char buffer [20000];
	int size;

	while(connectionTmp->run)
	{

		size = connectionTmp->socket->read(buffer, 20000);

		if (size > 0)
		{
			// on stocke le message reçu dans la file d'attente de traitement du deployer
			//	deployer->addMessage(buffer, size);
			connectionTmp->waitingPackets->push(buffer, size);
		}
		else
		{
			connectionTmp->stop();
		}
	}
	return NULL;
}
void Connection::start()
{
	// On crée un thread
    pthread_create(&thread, NULL, listenSocket, this);
}

void Connection::stop()
{
	run = false;
	socket->close();
}


Socket* Connection::getSocket()
{
	return socket;
}



