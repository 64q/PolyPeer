#include <iostream>
#include <cstring>

#include "../include/Socket.hpp"
#include "../include/BaseSocket.hpp"

using namespace std;

Socket::Socket(char* address, int port)
{
	connect(address, port);
}

Socket::Socket(int descripteur)
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

void Socket::connect(char* address, int port)
{
	struct hostent *hostinfo = NULL;
	SOCKADDR_IN sin = { 0 }; /* initialise la structure avec des 0 */
	const char *hostname = address;

	hostinfo = gethostbyname(hostname); /* on récupère les informations de l'hôte auquel on veut se connecter */
	if (hostinfo == NULL) /* l'hôte n'existe pas */
	{
		cout << "Unknown host "  << hostname << endl;
		exit(EXIT_FAILURE);
	}

	sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr; /* l'adresse se trouve dans le champ h_addr de la structure hostinfo */
	sin.sin_port = htons(port); /* on utilise htons pour le port */
	sin.sin_family = AF_INET;


	if (::connect(descripteur,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		cout << "connect()" << endl;
		exit(errno);
	}


}

void Socket::send(const char* data)
{
	if (::send(descripteur, data, strlen(data), 0) < 0)
	{
		cout << "send()" << endl;
		exit(errno);
	}
}

int Socket::read(char* buffer, int sizeBuffer)
{
	int size = 0;

	if ((size = recv(descripteur, buffer, sizeBuffer, 0)) < 0)
	{
		cout << "recv()" << endl;
		cout << strerror(errno) << endl;
		exit(errno);
	}
	
	return size;
}
