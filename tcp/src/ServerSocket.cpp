#include <iostream>

#include <ServerSocket.hpp>
#include <Socket.hpp>

using namespace std;

ServerSocket::ServerSocket(int port) :
	port(port)
{
	//initialisation du serveur d'écoute
	SOCKADDR_IN sin = {0};

	sin.sin_addr.s_addr = htonl(INADDR_ANY); /* nous sommes un serveur, nous acceptons n'importe quelle adresse */
	sin.sin_family = AF_INET;

	// On écoute le port défini en paramètre
	sin.sin_port = htons(port);

	// liaison avec le port
	if (bind (descripteur, (SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
	{
		throw BindException();
	}

	// On permet la connexion avec un nombre illimité de socket (sinon changer le deuxième paramètre de listen() )
	if (listen(descripteur, 0) == SOCKET_ERROR)
	{
//		cout <<"listen()" << endl;
		exit(errno);
	}
}

ServerSocket::~ServerSocket()
{


}

Socket* ServerSocket::accept()
{

	SOCKADDR_IN csin = {0};
	SOCKET csock;

	socklen_t sinsize = sizeof csin;
	//on récupère le descripteur de la socket de la demande reçue
	//(on fait appel à la fonction accept() système, il faut donc sortir de l'espace de nommage de la méthode avec :: )
	csock = ::accept(descripteur, (SOCKADDR *)&csin, &sinsize);

	if (csock == INVALID_SOCKET)
	{
		throw AcceptException();
	}
	else
	{
		//on retourne la nouvelle Socket avec l'adresse ip en deuxième paramètre
		return new Socket(csock, inet_ntoa(csin.sin_addr));
	}
}



