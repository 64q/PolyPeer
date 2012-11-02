#include <iostream>
#include <cstring>
#include <cmath>

#include <BaseSocket.hpp>
#include <Socket.hpp>
#include <TcpExceptions.hpp>

using namespace std;

Socket::Socket(std::string address, int port) :
	timeWaitForMTUInMc(50),
	numberPacketInvalid(0),
	numberPacketValid(0)

{
	connect(address, port);
}

Socket::Socket(int descripteur, std::string ipAdress) :
	ipAdress(ipAdress),
	timeWaitForMTUInMc(50),
	numberPacketInvalid(0),
	numberPacketValid(0)
{
	this->descripteur = descripteur;
}

Socket::Socket() :
	timeWaitForMTUInMc(50),
	numberPacketInvalid(0),
	numberPacketValid(0)
{

}

Socket::~Socket()
{
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

	return size;
}

std::string Socket::getIpAdress()
{
	return ipAdress;
}

void Socket::manageWaitingTimeWithPacketState(bool stateValid)
{
	if(stateValid)
	{
		numberPacketValid++;
	} else
	{
		numberPacketInvalid++;
		numberPacketValid = 0;
	}
	// le troisieme paquet invalide ca devient inquietant
	// donc on augmante le temps
	if (numberPacketInvalid > 4)
	{
		// on reparametre le temps d'attente
		timeWaitForMTUInMc += 25;
		// init des compteurs
		numberPacketValid = 0;
		numberPacketInvalid = 0;
	}
	// si on a beacoup de paquets valide on tente une diminution du temps
	// permet de réaugmenter le débit
	/*if (numberPacketValid > 1000)
	{
		// on reparametre le temps d'attente
		timeWaitForMTUInMc -= 1;
		// init des compteurs
		numberPacketValid = 0;
		numberPacketInvalid = 0;
	}*/
	// valeurs extremes tolérées
	if(timeWaitForMTUInMc > 12000)
		timeWaitForMTUInMc = 12000;
	if(timeWaitForMTUInMc < 0)
		timeWaitForMTUInMc = 0;
}



