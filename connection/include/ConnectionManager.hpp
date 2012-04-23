#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <map>
#include <string>
#include <vector>
#include <Connection.hpp>

class ConnectionManager
{
	public:
		ConnectionManager(std::vector<char*>* waitingMessage);
		virtual ~ConnectionManager();

		void addConnection(std::string name, Socket* socket);
	protected:

	private:
		std::map<std::string, Connection*> listConnections;
		std::vector<char*>* waitingMessage;
};

#endif // CONNECTIONMANAGER_H
