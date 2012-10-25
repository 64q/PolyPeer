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
    //cout << "connect stop"<<endl;
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
		//cout << "size "<<size<<endl<<flush;
		if (size > 0)
		{
		    Data d;
		    d.add(buffer, size);
			//cout << "size du paquet "<<size<<endl;
			Packet tmp(d);
			if(tmp.isValid())
			{
			    //on ajoute l'adresse ip d'où provient le paquet
                tmp.setAddress(connectionTmp->socket->getIpAdress());

                // On envoie au socket l'état du packet (si il est intègre)
                // pour qu'il adapte son dans d'attente si besoin
                connectionTmp->socket->manageWaitingTimeWithPacketState(tmp.isValid());

                //cout << "------>" << connectionTmp->socket->getIpAdress() << endl;
                //on agit suivant le paquet
                PacketCallback::getPacketCallback()->packetOperation(tmp);
                d.clear();
			}



		}
		else
		{
            //cout << "il veut stopper"<<endl;
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
