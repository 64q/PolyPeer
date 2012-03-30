#ifndef __H__WEBSERVER__
#define __H__WEBSERVER__

// Spécifique map
#include <map>

// Spécifique pour les sockets
#include <arpa/inet.h> // nécessaire pour les sockaddr

typedef std::string (*route_handler)(std::string, std::string);

class WebServer
{
public:
	/**
	 * Lancement du serveur Web
	 */
	void run();
	
	/**
	 * Arrêt du serveur Web
	 */
	void stop();
	
	/**
	 * Accès au singleton du serveur Web
	 */
	static WebServer* getInstance();
	
	/**
	 * Destructeur
	 */
	~WebServer();
	
private:
	/**
	 * Constructeur d'un WebServer
	 */
	WebServer(const int port);
	
	/**
	 * Instance du WebServer
	 */
	static WebServer* instance;
	
	/**
	 * Socket du server
	 */
	int socket;
	
	/**
	 * sockaddr client et server
	 */
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
	
	/**
	 * Port d'écoute du serveur web
	 */
	int port;
	
	std::map<std::string, route_handler> routes;
};


std::string default_route(std::string get, std::string post);
std::string login_route(std::string get, std::string post);

#endif
