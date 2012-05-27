#ifndef POLYPEERSERVER_H
#define POLYPEERSERVER_H

// header
#include <BaseServer.hpp>

// forward declaration
class ServerData;
class WebServer;

/**
 * Serveur principale de Polypeer.
 * gère le lancement de tous les threads de traitement
 */
class PolypeerServer : public BaseServer
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
	 * Récupérer la structure principale
	 */
	inline ServerData& getServerData() { return *(this->sData); }
	
	int getClientPort() {return clientPort; }
	
	/**
	 * Destructeur de PolypeerServer
	 */
	~PolypeerServer();
	
	/**
	 * Accès au singleton du serveur
	 */
	static PolypeerServer* getInstance();
	
	friend void* thread_initConnection(void* data);
	
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
	 * Méthode de run
	 */
	static void run();
	
	/**
	 * initialisation des connexions
	 */
	 void initConnections();
	
	/**
	 * Structure principale du programe
	 */
	ServerData* sData;
	
	/**
	 * Instance du webserver
	 */
	WebServer* webserver;
	
	/**
	 * port client
	 */
	int clientPort;
	
	
};

// Fonction thread
void* thread_initConnection(void* data);


#endif //POLYPEERSERVER_H
