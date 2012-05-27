#include <Connection.hpp>
#include <PacketCallback.hpp>
#include <PacketAddHost.hpp>
#include <iostream>

using namespace std;

Connection::Connection(Socket* socket): socket(socket)
{
	name = socket->getIpAdress();
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
			Packet tmp(buffer, size);
			//on ajoute l'adresse ip d'où provient le paquet
			tmp.setAddress(connectionTmp->socket->getIpAdress());

			//on agit suivant le paquet
			PacketCallback::getPacketCallback()->packetOperation(tmp);
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


void Connection::throwUpdatePacket()
{
	
	PacketAddHost packet(name);
	PacketCallback::getPacketCallback()->packetOperation(packet);


}
