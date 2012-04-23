#include <Connection.hpp>

#include <iostream>
using namespace std;

Connection::Connection(Socket* socket, std::vector<char*>* waitingMessage): socket(socket), waitingMessage(waitingMessage)
{
	//ctor
}

Connection::~Connection()
{
	//dtor
}

void* listenSocket(void* connection)
{
	Connection* connectionTmp = (Connection*)connection;
	connectionTmp->run = true;
	char buffer [300];
	int size;

	while(connectionTmp->run)
	{
		size = connectionTmp->socket->read(buffer, 300);
		if (size > 0)
		{
			// on stocke le message reçu dans la file d'attente de traitement du deployer
			//	deployer->addMessage(buffer, size);
			connectionTmp->waitingMessage->push_back(buffer);
		}
	}
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





