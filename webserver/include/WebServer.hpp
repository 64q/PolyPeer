#ifndef __H__WEBSERVER__
#define __H__WEBSERVER__

// Spécifique map
#include <map>

// Spécifique pour les sockets
#include <arpa/inet.h> // nécessaire pour les sockaddr

#include "WebRequest.hpp"

/**
 * typedef permettant d'avoir un ptr sur une fonction de handler de route
 */
typedef std::string (*route_handler)(WebRequest&);

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
	
	/**
	 * Booléen nécessaire pour controler le serveur web
	 */
	bool isRunning;
	
	/**
	 * Map stockant les routes http
	 */
	std::map<std::string, route_handler> routes;
};

/**
 * Route par défaut
 */
std::string default_route(WebRequest& request);

/**
 * Route not found
 */
std::string notfound_route(WebRequest& request);

std::string deployment_route(WebRequest& request);

#endif
