#ifndef __H__PPWEBSERVER__
#define __H__PPWEBSERVER__

// Spécifique pour les sockets
#include <sys/types.h>  
#include <sys/socket.h>

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
	
	int socket;
	
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
	
	/**
	 * Port d'écoute du serveur web
	 */
	int port;
};

#endif
