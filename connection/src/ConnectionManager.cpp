#include <string>
#ifdef WIN32 /* si vous êtes sous Windows */
	#define sleep(t) Sleep(t)
#endif


#include <ConnectionManager.hpp>
#include <signal.h>


ConnectionManager::ConnectionManager(int port)
{
	bool bind = false;
	run = true;
	while(!bind && run)
	{
		try
		{
			serverSocket = new ServerSocket(port);
			bind = true;
		}catch(BindException)
		{
			cout << "impossible de lier le port d'écoute numéro :" << port << endl;
			cout << "tentative de reconnexion dans 5 secondes" << endl;
			delete serverSocket;
			sleep(5);
		}
	}


}

ConnectionManager::~ConnectionManager()
{
	cout << "CM detruit"<<endl<<flush;
	stop();
}

void ConnectionManager::addConnection(std::string name, Socket* socket)
{

	Connection* tmp = new Connection(socket);
	tmp->throwUpdatePacket();
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
	while(connectionManagerTmp->run && )
	{
		cout << "en attente "<<endl;
		sockTmp = connectionManagerTmp->serverSocket->accept();
		cout << "connexion "<<endl;

		connectionManagerTmp->addConnection(sockTmp->getIpAdress(), sockTmp);

	}
	return NULL;

}


void ConnectionManager::start()
{
	pthread_create(&thread, NULL, runFct, this);

}

void ConnectionManager::stop()
{
	cout << "CM stop"<<endl<<flush;
	run = false;

	std::map<std::string, Connection*>::const_iterator itr;
	for(itr = listConnections.begin(); itr!=listConnections.end(); ++itr)
	{
		delete itr->second;
	}

	serverSocket->close();
//	kill(thread, 9);
	cout << "serverSocketClose"<<endl;
}

void ConnectionManager::sendTo(std::string dest, Packet packet)
{//cout << "CM sento"<<endl<<flush;
	Connection* connection = listConnections[dest];
	cout << "envoie à " << dest << " de "<< packet.getType()<<endl;

	if(connection != NULL)
	{
		connection->getSocket()->send(packet.serialize());
	}else
	{
		cout << "l'adresse ip est inconnu dans le ConnectionManager, tentative de connexion..." << endl;

		try
		{
			Socket* sock = new Socket(dest, 5555);
			sleep(5);
			addConnection(dest, sock);
		}catch(HostNotFoundException){ cout << "host not found"<<endl;}
		catch(ConnectionException){}

	}
}

void ConnectionManager::wait()
{
	pthread_join(thread, NULL);
	cout << "ok"<<endl;
}

void ConnectionManager::removeConnection(std::string ip)
{
	Connection* connec = listConnections[ip];
	if(connec != NULL)
	{
		listConnections.erase(ip);
	}
}
