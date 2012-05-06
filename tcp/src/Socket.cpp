#include <iostream>
#include <cstring>

#include <BaseSocket.hpp>
#include <Socket.hpp>
#include <TcpExceptions.hpp>

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

	size = recv(descripteur, buffer, sizeBuffer, 0);


	return size;
}
