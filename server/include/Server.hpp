#ifndef __H_SERVER__
#define __H_SERVER__

#include <map>

#include <WebServer.hpp>
#include <Logger.hpp>
#include <Host.hpp>

class Server
{
public:
	void run();
	
	void stop();
	
	void restart();
	
	Host getHost(std::string name);
	
	static Server* getInstance(const int port = 9696);

	virtual ~Server();

private:
	Server(const int port);
	
	bool isRunning;
	
	bool debug;
	
	static Server* instance;
	
	WebServer* webserver;
	
	Logger logger;
	
	std::map<std::string, Host> hosts;
};

#endif
