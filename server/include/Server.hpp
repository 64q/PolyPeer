#ifndef __H_SERVER__
#define __H_SERVER__

#include <WebServer.hpp>
#include <Logger.hpp>

class Server
{
public:
	void run();
	
	void stop();
	
	void restart();
	
	static Server* getInstance(const int port = 9696);

	virtual ~Server();

private:
	Server(const int port);
	
	bool isRunning;
	
	bool debug;
	
	static Server* instance;
	
	WebServer* webserver;
	
	Logger logger;
};

#endif
