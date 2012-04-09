#include <iostream>

#include "../include/ServerSocket.hpp"
#include "../include/Socket.hpp"

using namespace std;

ServerSocket::ServerSocket(int port) :
	port(port)
{
	//initialisation du serveur d'�coute
	SOCKADDR_IN sin = {0};

	sin.sin_addr.s_addr = htonl(INADDR_ANY); /* nous sommes un serveur, nous acceptons n'importe quelle adresse */
	sin.sin_family = AF_INET;

	// On �coute le port d�fini en param�tre
	sin.sin_port = htons(port);

	// liaison avec le port
	if (bind (descripteur, (SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
	{
		cout << "error bind" << endl;
		exit(errno);
	}

	// On permet la connexion avec un nombre illimit� de socket (sinon changer le deuxi�me param�tre de listen() )
	if (listen(descripteur, 0) == SOCKET_ERROR)
	{
		cout <<"listen()" << endl;
		exit(errno);
	}
}

ServerSocket::~ServerSocket()
{
	//voir si il faut laisser �a ici
	#ifdef WIN32
	WSACleanup();
	#endif
}

Socket* ServerSocket::accept()
{


	SOCKADDR_IN csin = {0};
	SOCKET csock;

	socklen_t sinsize = sizeof csin;

	//on r�cup�re le descripteur de la socket de la demande re�ue
	//(on fait appel � la fonction accept() syst�me, il faut donc sortir de l'espace de nommage de la m�thode avec :: )
	csock = ::accept(descripteur, (SOCKADDR *)&csin, &sinsize);

	if (csock == INVALID_SOCKET)
	{
		cout << "accept()" << endl;
		cout << WSAGetLastError() << endl;
		exit(errno);
	}
	else
	{
		return new Socket(csock);
	}
}




