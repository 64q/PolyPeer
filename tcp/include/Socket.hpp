#ifndef SOCKET_H
#define SOCKET_H
#include "BaseSocket.hpp"

class Socket: public BaseSocket
{
public:
	Socket();
	Socket(char* address, int port);
	Socket(int descripteur);
	// Socket(Socket& sock);
	~Socket();
	
	void connect(char* address, int port);
	void send(const char* data);
	int read(char* buffer, int sizeBuffer);
};


#endif // SOCKET_H
