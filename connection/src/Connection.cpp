#include <Connection.hpp>

#include <iostream>
using namespace std;

Connection::Connection(Socket* socket): socket(socket)
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
			// on réagit en fonction du type de paquet

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



