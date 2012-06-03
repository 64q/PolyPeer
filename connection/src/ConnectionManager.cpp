#include <string.h> // .h a cause de memcpy
#ifdef WIN32 /* si vous êtes sous Windows */
	#define sleep(t) Sleep(t)
#endif


#include <ConnectionManager.hpp>

#include <vector>

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
	stop();
}

void ConnectionManager::addConnection(std::string name, Socket* socket)
{

	Connection* tmp = new Connection(socket);
	tmp->throwUpdatePacket();

	mutex.lock();
	listConnections[name] = tmp;
	mutex.unlock();

	tmp->start();

}

Connection* ConnectionManager::getConnection(std::string name)
{
	return listConnections[name];
}

void* runFct(void* connectionManager)
{
    try
    {

        ConnectionManager* connectionManagerTmp = (ConnectionManager*)connectionManager;
        connectionManagerTmp->run = true;
        Socket* sockTmp;
        while(connectionManagerTmp->run )
        {

            sockTmp = connectionManagerTmp->serverSocket->accept();

            connectionManagerTmp->addConnection(sockTmp->getIpAdress(), sockTmp);

        }
    }catch(AcceptException e)
    {

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
    mutex.lock();
	std::map<std::string, Connection*>::const_iterator itr;

	std::vector<Connection*> ipAdress;
	for(itr = listConnections.begin(); itr!=listConnections.end(); ++itr)
	{
	    ipAdress.push_back(itr->second);
	}
    mutex.unlock();
	std::vector<Connection*>::const_iterator itrV;
    for(itrV = ipAdress.begin(); itrV!=ipAdress.end(); ++itrV)
	{
	    (*itrV)->stop();
	}






//    cout <<"fin destruction"<<endl;
	serverSocket->close();


}

void ConnectionManager::sendTo(std::string dest, Packet packet)
{
	mutex.lock();
	Connection* connection = listConnections[dest];
	mutex.unlock();
	//cout << "envoie à " << dest << " de "<< packet.getType()<<endl;

	if(connection != NULL)
	{
		connection->getSocket()->send(packet.serialize());
	}else
	{


		try
		{
			Socket* sock = new Socket(dest, 5555);
			sleep(5);
			addConnection(dest, sock);
		}catch(HostNotFoundException){}
		catch(ConnectionException){}

	}
}

void ConnectionManager::wait()
{
	pthread_join(thread, NULL);

}

void ConnectionManager::removeConnection(std::string ip)
{

	mutex.lock();
	Connection* connec = listConnections[ip];

	if(connec != NULL)
	{
		listConnections.erase(ip);
	}
	mutex.unlock();
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
	if ((hptr=gethostbyname(bcastAddr)))
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

	if (sendto(sd,(char*)buf,len,0,(sockaddr*)&name,sizeof(name))!=(int)len)
	{
		return(false);
	}

	return(true);
}
