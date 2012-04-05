#include <iostream>
using namespace std;

#include "../include/ServerSocket.hpp"
#include "../include/Socket.hpp"





ServerSocket::ServerSocket(int port):port(port)
{



	SOCKADDR_IN sin = { 0 };

	sin.sin_addr.s_addr = htonl(INADDR_ANY); /* nous sommes un serveur, nous acceptons n'importe quelle adresse */

	sin.sin_family = AF_INET;

	sin.sin_port = htons(port);

	if(bind (descripteur, (SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
	{
		 cout << "error bind" << endl;
		 exit(errno);
	}

	if(listen(descripteur, 0) == SOCKET_ERROR)
    {
        cout <<"listen()" << endl;
        exit(errno);
    }

}

ServerSocket::~ServerSocket()
{
    cout<<"serveur closed"<<endl;
}

Socket& ServerSocket::accept()
{

    SOCKADDR_IN csin = { 0 };
    SOCKET csock;

    socklen_t sinsize = sizeof csin;

    csock = ::accept(descripteur, (SOCKADDR *)&csin, &sinsize);

    if(csock == INVALID_SOCKET)
    {
        cout << "accept()" << endl;
        exit(errno);

    }
    else{

        return *(new Socket(csock));
    }


}




