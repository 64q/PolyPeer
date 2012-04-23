#ifndef CONNECTION_H
#define CONNECTION_H
#include <Socket.hpp>
#include <pthread.h>
#include <vector>

class Connection
{
	public:
		Connection(Socket* socket, std::vector<char*>* waitingMessage);
		virtual ~Connection();

		void start();
		void stop();

	protected:
	private:
		Socket* socket;
		std::string name;
		pthread_t thread;
		bool run;
		std::vector<char*>* waitingMessage;

		friend void* listenSocket(void* connection);

		//void* listen(void* connection);
};

#endif // CONNECTION_H
