#include <iostream>
using namespace std;

#include "../include/BaseSocket.hpp"




BaseSocket::BaseSocket()
{
    //initialisation propre à windows
    #ifdef WIN32
    WSADATA wsa;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa);
    if(err < 0)
    {
        cout << "WSAStartup failed !" << endl;
        exit(EXIT_FAILURE);
    }
	#endif

    //initialisation de la socket
    descripteur = socket(AF_INET, SOCK_STREAM, 0);
	if(descripteur == INVALID_SOCKET)
	{
		 cout << "socket()" << endl;
		 exit(EXIT_FAILURE);
	}

}

BaseSocket::~BaseSocket()
{
    close();

}

void BaseSocket::close()
{

    #ifdef WIN32
        WSACleanup();
    #endif

    closesocket(descripteur);
}
