#ifndef CONNECTION_H
#define CONNECTION_H
#include <Socket.hpp>
#include <pthread.h>
#include <vector>

#include <WaitingPackets.hpp>

class Connection
{
	public:
		Connection(Socket* socket, WaitingPackets* cm);
		virtual ~Connection();

		void start();
		void stop();

		Socket* getSocket();

	private:
		Socket* socket;
		std::string name;
		pthread_t thread;
		bool run;
		WaitingPackets* waitingPackets;

		friend void* listenSocket(void* connection);


};

#endif // CONNECTION_H
