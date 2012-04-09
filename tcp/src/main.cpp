#include <iostream>

#include "../include/ServerSocket.hpp"

using namespace std;

int main()
{

	ServerSocket server(5556);
	cout << "en attente" << endl;

	Socket* sock;
	while (true)
	{
		sock = server.accept();
		sock->send("crotte");
		sock->close();
		delete sock;

	}

	server.close();

//	    Socket sock("localhost", 5556);
//
//	    char buff[200];
//	    int taille = sock.read(buff, 200);
//	    cout << taille<<" : "<<buff << endl;
//	    sock.close();

	return 0;
}



















