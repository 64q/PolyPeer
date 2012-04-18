#ifndef __H_BASESERVER__
#define __H_BASESERVER__

#include <Logger.hpp>

/**
 * Le BaseServer fournit une interface complète pour batir un serveur
 * standard dans l'application PolyPeer.
 */
class BaseServer
{
public:
	/**
	 * Méthode permettant de démarrer le serveur
	 * @param int port
	 * 	le port sur lequel le serveur va écouter
	 */
	virtual void start(const int port) = 0;
	
	/**
	 * Méthode permettant de stopper le serveur sans toutefois
	 * stopper le programme.
	 */
	virtual void stop() = 0;
	
	/**
	 * Méthode permettant de redémarrer le serveur
	 */
	virtual void restart() = 0;
	
	/**
	 * Méthode permettant de faire tourner le serveur
	 */
	virtual void run() = 0;
	
	/**
	 * Destructeur de BaseServer
	 */
	virtual ~BaseServer();
	
protected:
	/**
	 * Le constructeur, le constructeur par copie et l'opérateur = sont privés
	 * afin d'éviter l'instanciation de plusieurs servers.
	 */
	BaseServer(const std::string);
	BaseServer(const BaseServer&);
	BaseServer& operator=(const BaseServer&);
	
	/**
	 * Logger du server, sert à stocker dans un fichier texte les actions du serv.
	 */
	Logger logger;
	
	/**
	 * Permet de savoir si le serveur est en mode de fonctionnement ou pas.
	 */
	bool running;
	
	/**
	 * Le mode debug permet de logger plus d'informations dans les fichiers de log.
	 */
	bool debug;
	
	/**
	 * Port d'écoute du serveur
	 */
	int port;
};

#endif
