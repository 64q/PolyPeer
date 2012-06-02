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
	while(connectionManagerTmp->run )
	{
		//cout << "en attente "<<endl;
		sockTmp = connectionManagerTmp->serverSocket->accept();
		//cout << "connexion "<<endl;

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



bool ConnectionManager::WOL(const char *macAddr,const char *bcastAddr)
{


	SOCKET sd;	// file descriptor of the socket
	struct sockaddr_in name;
	char optval;
	struct hostent *hptr;
	const unsigned int len=17*6;
	unsigned char buf[len];
	unsigned char mac[6];
	int i;

	for (i=0;*macAddr!='\0' && i<6*3;macAddr++)
	{
		if (i%3==0) mac[i/3]=0;
		if (i%3==2)
		{
			if ((*macAddr!=':') && (*macAddr!='-')) return(false);
		}
		else
		{
			if ((*macAddr>='0') && (*macAddr<='9')) mac[i/3]|=(*macAddr-'0')<<((1-(i%3))*4);
			else if ((*macAddr>='a') && (*macAddr<='f')) mac[i/3]|=(*macAddr-'a'+10)<<((1-(i%3))*4);
			else if ((*macAddr>='A') && (*macAddr<='F')) mac[i/3]|=(*macAddr-'A'+10)<<((1-(i%3))*4);
			else return(false);
		}
		i++;
	}
	if (*macAddr!='\0') return(false);
	
	for (i=0;i<6;i++) buf[i]=0xff;
	for (i=0;i<16;i++) memcpy(buf+6+i*6,mac,6);

	memset(&name,0,sizeof(name));
	name.sin_family=AF_INET;
	name.sin_port=htons(9);
	if (hptr=gethostbyname(bcastAddr))
	{
		memcpy(&name.sin_addr.s_addr,hptr->h_addr,hptr->h_length);
		name.sin_family=hptr->h_addrtype;
	}
	else if ((name.sin_addr.s_addr=inet_addr(bcastAddr))>-1)
	{
		name.sin_family=AF_INET;
	}
	else return(false);

	if ((sd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))<0)
	{
		return(false);
	}

	optval=1;
	if (setsockopt(sd,SOL_SOCKET,SO_BROADCAST,&optval,sizeof(optval))<0)
	{
		return(false);
	}

	if (sendto(sd,(char*)buf,len,0,(sockaddr*)&name,sizeof(name))!=len)
	{
		return(false);
	}

	return(true);
}
