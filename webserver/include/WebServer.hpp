#ifndef __H__WEBSERVER__
#define __H__WEBSERVER__

// Spécifique map
#include <map>

#include <mongoose.h>

#include <BaseServer.hpp>
#include <Logger.hpp>

/**
 * Le web server permet de gérer intégralement l'interface web de controle
 * du programme PolyPeer. Il donne acccès à des pages web et à des controles
 * via les routes définies.
 */
class WebServer : public BaseServer
{
public:
	/**
	 * Démarrage du serveur
	 */
	void start();

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
	 * Accès au singleton du serveur Web
	 */
	static WebServer* getInstance();
	
	/**
	 * Destructeur
	 */
	~WebServer();
	
protected:
	/**
	 * Constructeur d'un WebServer
	 * @param int port
	 * 	le port d'écoute du serveur
	 * @param string path
	 * 	chemin d'accès aux templates
	 */
	WebServer();
	
	/**
	 * Lancement du serveur Web
	 */
	void run();
	
	mg_context* context;
	
	/**
	 * Instance du WebServer
	 */
	static WebServer* instance;
};

/**
 * Fonction d'handle des events sur le serveur web
 */
void* eventHandler(mg_event event, mg_connection *conn, const mg_request_info *request_info);

#endif
