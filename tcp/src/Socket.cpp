#include <iostream>
#include <cstring>

#include <BaseSocket.hpp>
#include <Socket.hpp>
#include <TcpExceptions.hpp>

using namespace std;

Socket::Socket(std::string address, int port)
{
	connect(address, port);
}

Socket::Socket(int descripteur, std::string ipAdress):ipAdress(ipAdress)
{
	this->descripteur = descripteur;
}

Socket::Socket()
{

}

Socket::~Socket()
{

	cout<<"client closed"<<endl;

}

void Socket::connect(std::string address, int port)
{
	ipAdress = address;
	struct hostent *hostinfo = NULL;
	SOCKADDR_IN sin = { 0 }; /* initialise la structure avec des 0 */
	const char *hostname = address.c_str();

	hostinfo = gethostbyname(hostname); /* on récupère les informations de l'hôte auquel on veut se connecter */
	if (hostinfo == NULL) /* l'hôte n'existe pas */
	{
		throw HostNotFoundException();
	}

	sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr; /* l'adresse se trouve dans le champ h_addr de la structure hostinfo */
	sin.sin_port = htons(port); /* on utilise htons pour le port */
	sin.sin_family = AF_INET;


	if (::connect(descripteur,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		throw ConnectionException();
	}


}

bool Socket::send(const char* data, int size)
{
	if (::send(descripteur, data, size, 0) < 0)
	{
		return false;
	}
	return true;
}

bool Socket::send(const Data& data)
{
	return send(data.c_str(), data.getSize());
}

int Socket::read(char* buffer, int sizeBuffer)
{
	int size = 0;
	//essayer avec MSG_WAITALL à la place de 0
	size = recv(descripteur, buffer, sizeBuffer, 0);
	
	if(size>0)
	{
	 //On vérifie qu'il n'y a plus rien à lire
		fd_set rfds;
		 struct timeval tv;
		 int retval;
		 bool complete = false;
		 
		 while(!complete)
		 {
			 // Surveiller stdin (fd 0) en attente d'entrées
			 FD_ZERO(&rfds);
			 FD_SET(descripteur, &rfds);
			 // Pendant 0 secondes maxi
			 tv.tv_sec = 0;
			 tv.tv_usec = 10000;
			 cout << "avant retval"<<endl;
			 retval = select(descripteur+1, &rfds, NULL, NULL, &tv);
			 // Considerer tv comme indéfini maintenant !
			 cout << "retval "<<retval <<endl;
			 if(retval!=-1 )
			 {
				 if (retval && retval!=-1)
				 {
				 	cout <<"reconstruction"<<endl;
				 	char* buffTmp = new char[20000];

				 	int sizeTmp = recv(descripteur, buffTmp, 20000, 0);
				 	
				cout << "taille de base "<<size<<" taille ajout "<<sizeTmp<<endl;
					for(int i = size; i < size+sizeTmp; i++)
					{
						buffer[i] = buffTmp[i-size];
					}
					size+=sizeTmp;
					delete [] buffTmp;
				 }
				 else
				 {
				 	cout <<"pas de reconstruction"<<endl;
					complete = true;
				}
			}else
			{
				size = -1;
				complete = true;
			}
		}
	}

	return size;
}

std::string Socket::getIpAdress()
{
	return ipAdress;
}


