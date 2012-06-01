#ifndef __H__WEBSERVER__
#define __H__WEBSERVER__

// Spécifique map
#include <map>
#include <vector>

#include <mongoose.h>

#include <BaseServer.hpp>
#include <Logger.hpp>

/** 
 * Typedef pour créer facilement des handlers sur les routes appelées par le client web
 */
typedef void (*route_handler)(mg_connection*, const mg_request_info*);

/**
 * Structure pour configurer le serveur
 */
struct WebServerConfig {
	int port;
	int nthreads;
	std::string root;
	std::string pwfile;
	std::string domain;
};

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
	 * Configure le serveur (a executer en premier)
	 */
	void setConfig(WebServerConfig* opt);
	
	/**
	 * Permet de passer en mode debug et inversement
	 */
	void toggleDebug();
	
	/**
	 * Renvoie l'état du serveur (en debug ou pas)
	 * @return bool
	 * 	etat debug
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
	 */
	WebServer();
	
	/**
	 * Lancement du serveur Web
	 */
	static void run();
	
	/**
	 * Contexte nécessaire pour mongoose
	 */
	mg_context* context;
	
	/**
	 * Routes du serveur
	 */
	std::map<std::string, route_handler> routes;
	
	/**
	 * Instance du WebServer
	 */
	static WebServer* instance;

	/**
	 * Fonction amie pour accéder facilement aux attrs du webserver
	 */
	friend void* eventHandler(mg_event, mg_connection*, const mg_request_info*);
};

/**
 * Fonction d'handle des events sur le serveur web
 * @param mg_event
 * 	evenement déclenché par une requête
 * @param mg_connection*
 * 	connexion courante
 * @param mg_request*
 * 	contient tous les paramètres de la requête reçue
 */
void* eventHandler(mg_event event, mg_connection *conn, const mg_request_info *request_info);

#endif
