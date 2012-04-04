#ifndef __H__WEBSERVER__
#define __H__WEBSERVER__

// Spécifique map
#include <map>

// Spécifique pour les sockets
#include <arpa/inet.h> // nécessaire pour les sockaddr

#include "WebRequest.hpp"

/**
 * Port du serveur Web
 */
const int WEBSERVER_PORT = 6969;

/**
 * Dossier de base du contenu du serveur web
 */
const std::string WEBSERVER_ROOT = "webpages";

/**
 * typedef permettant d'avoir un ptr sur une fonction de handler de route
 * @param WebRequest
 * 	requête récupérée depuis le client
 * @return
 * 	contenu à envoyer au navigateur client
 */
typedef std::string (*route_handler)(WebRequest&);

/**
 * Le web server permet de gérer intégralement l'interface web de controle
 * du programme PolyPeer. Il donne acccès à des pages web et à des controles
 * via les routes définies.
 */
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
	 * Restart du serveur Web
	 */
	void restart();
	
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
	int serv_socket;
	
	/**
	 * Socket du client
	 */
	int cli_socket;
	
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

#endif
