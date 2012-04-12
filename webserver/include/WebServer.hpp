#ifndef __H__WEBSERVER__
#define __H__WEBSERVER__

// Spécifique map
#include <map>

// Spécifique pour les sockets
#include <arpa/inet.h> // nécessaire pour les sockaddr

#include <ServerSocket.hpp>
#include <WebRequest.hpp>
#include <Logger.hpp>

/**
 * Port du serveur Web
 */
static const int WEBSERVER_PORT = 6969;

/**
 * typedef permettant d'avoir un ptr sur une fonction de handler de route
 * @param WebRequest
 * 	requête récupérée depuis le client
 * @return string
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
	 * Permet de passer en mode debug et inversement
	 */
	void toggleDebug();
	
	/**
	 * Renvoie l'état du serveur (en debug ou pas)
	 */
	bool isDebug();
	
	/**
	 * Retourne le chemin vers les ressources web
	 */
	std::string getResourcesPath();
	
	/**
	 * Défini le chemin d'accès aux ressources web
	 */
	void setResourcesPath(const std::string path);
	
	/**
	 * Accès au singleton du serveur Web
	 */
	static WebServer* getInstance();
		
	/**
	 * Logger du webserver
	 */
	Logger logger;
	
	/**
	 * Destructeur
	 */
	~WebServer();
	
private:
	/**
	 * Constructeur d'un WebServer
	 */
	WebServer(const int port, const std::string path);
	
	/**
	 * Instance du WebServer
	 */
	static WebServer* instance;
	
	/**
	 * Dossier de base du contenu du serveur web
	 */
	std::string resourcesPath;
	
	/**
	 * SocketServer
	 */
	ServerSocket socket;
	
	/**
	 * Port d'écoute du serveur web
	 */
	int port;
	
	/**
	 * Booléen nécessaire pour controler le serveur web
	 */
	bool isRunning;
	
	/**
	 * Mode debug (active le tracage des requêtes HTTP)
	 * Si actif, il va écrire dans log/webserver.log des infos supplémentaires
	 * utiles pour le développeur désirant plus d'infos sur le trafic.
	 */
	bool debug;
	
	/**
	 * Map stockant les routes http
	 */
	std::map<std::string, route_handler> routes;
};

#endif
