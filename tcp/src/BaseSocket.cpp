#include <iostream>

#include <BaseSocket.hpp>

using namespace std;


int BaseSocket::nbInstance = 0;

BaseSocket::BaseSocket()
{
	// initialisation propre à windows
	#ifdef WIN32
	if(nbInstance == 0)
	{
		WSADATA wsa;
		int err = WSAStartup(MAKEWORD(2, 2), &wsa);
		if (err < 0)
		{
			cout << "WSAStartup failed !" << endl;
			exit(EXIT_FAILURE);
		}
	}

	#endif

	// initialisation de la socket
	descripteur = socket(AF_INET, SOCK_STREAM, 0);
	if (descripteur == (int)INVALID_SOCKET)
	{
		cout << "socket()" << endl;
		exit(EXIT_FAILURE);
	}

	nbInstance++;
}

BaseSocket::~BaseSocket()
{
	nbInstance--;
	if(nbInstance==0)
	{
		#ifdef WIN32
		WSACleanup();
		#endif
	}
    close();
}

void BaseSocket::close()
{
	//fermeture propre de la socket
	closesocket(descripteur);
}
