#ifndef POLYPEERSERVER_H
#define POLYPEERSERVER_H


#include <Logger.hpp>
#include <ServerData.hpp>

/**
 * Serveur principale de Polypeer.
 * gère le lancement de tous les threads de traitement
 */
class PolypeerServer
{
public:
	/**
	 * Lancement du seveur
	 */
	void start();
	
	/**
	 * Arret du serveur
	 */
	void stop();
	
	/**
	 * Redémarrage du serveur
	 */
	void restart();
	
	/**
	 * Destructeur de PolypeerServer
	 */
	~PolypeerServer();
	
	/**
	 * Accès au singleton du serveur
	 */
	static PolypeerServer* getInstance();
	
	/**
	 * Récupérer le logger du serveur
	 */
	Logger& getLogger();
	
	
private:
	/**
	 * Respet du patern singleton
	 */
	PolypeerServer();
	PolypeerServer(const PolypeerServer&);
	PolypeerServer& operator=(const PolypeerServer&);
	
	/**
	 * Instance du server
	 */
	static PolypeerServer* instance;
	
	/**
	 * Function contenant la boucle d'execution
	 */
	void run();
	
	/**
	 * condition d'exécution
	 */
	bool running;
	
	/**
	 * Port d'écoute du serveur
	 */
	int port;
	
	/**
	 * Logger du server, sert à stocker dans un fichier texte les actions
	 */
	Logger logger;
	
	/**
	 * Structure principale du programe
	 */
	ServerData* sData;
	
};


#endif //POLYPEERSERVER_H
