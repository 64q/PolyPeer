#ifndef POLYPEERCLIENT_H
#define POLYPEERCLIENT_H

// header
#include <BaseServer.hpp>

// forward declaration
class ClientData;

struct ClientOptions 
{
	std::string ip;
	int clientPort;
	int serverPort;
	bool daemon;
	std::string root;
};

/**
 * Client de Polypeer.
 * gère le lancement de tous les threads de traitement
 * Par Erwan
 */
class PolypeerClient : public BaseServer
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
	 * Méthode de config a lancer en premier
	 */
	void setConfig(ClientOptions* opt);

	/**
	 * Récupérer la structure principale
	 */
	inline ClientData* getClientData() { return (this->cData); }

	/**
	 * Destructeur de PolypeerClient
	 */
	~PolypeerClient();

	/**
	 * Accès au singleton du serveur
	 */
	static PolypeerClient* getInstance();


private:
	/**
	 * Respect du patern singleton
	 */
	PolypeerClient();
	PolypeerClient(const PolypeerClient&);
	PolypeerClient& operator=(const PolypeerClient&);

	/**
	 * Instance du server
	 */
	static PolypeerClient* instance;

	/**
	 * Méthode de run
	 */
	static void run();

	/**
	 * Structure principale du programe
	 */
	ClientData* cData;


};


#endif //POLYPEERSERVER_H
