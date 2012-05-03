#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <map>
#include <string>
#include <vector>
#include <Connection.hpp>
#include <WaitingPackets.hpp>

class ConnectionManager
{
	public:
		ConnectionManager(WaitingPackets* waitingPackets);
		virtual ~ConnectionManager();

		void addConnection(std::string name, Socket* socket);
		Connection* getConnection(std::string name);
	protected:

	private:
		std::map<std::string, Connection*> listConnections;
		WaitingPackets* waitingPackets;
};

#endif // CONNECTIONMANAGER_H
