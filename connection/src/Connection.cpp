#include <Connection.hpp>
#include <PacketCallback.hpp>
#include <PacketAddHost.hpp>
#include <PacketRemoveHost.hpp>
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
		cout << "size "<<size<<endl<<flush;
		if (size > 0)
		{
			Packet tmp(buffer, size);
			//on ajoute l'adresse ip d'où provient le paquet
			tmp.setAddress(connectionTmp->socket->getIpAdress());
			cout << "------>" << connectionTmp->socket->getIpAdress() << endl;
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
	throwRemoveConnection();
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

void Connection::throwRemoveConnection()
{
	PacketRemoveHost packet(name);
	PacketCallback::getPacketCallback()->packetOperation(packet);
}
