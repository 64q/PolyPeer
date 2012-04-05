#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "BaseSocket.hpp"
#include "Socket.hpp"

class ServerSocket : public BaseSocket{

	private:
		int port;


	public:
		ServerSocket(int port);
		~ServerSocket();
		Socket& accept();



};

#endif // SERVERSOCKET_H
