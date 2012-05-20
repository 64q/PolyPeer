#ifndef POLYPEERSERVER_H
#define POLYPEERSERVER_H


//#include <Logger.hpp>


class PolypeerServer
{
public:
	/**
	 * Démarrage du serveur
	 */
	void start();
	
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
	 * Accès au singleton du serveur
	 */
	static PolypeerServer* getInstance()
	{
		if (PolypeerServer::instance == NULL)
		{
			PolypeerServer::instance = new PolypeerServer();
		}
		return PolypeerServer::instance;
	}
	
	/**
	 * Destructeur
	 */
	~PolypeerServer();
	
private:
	
	PolypeerServer();
	
	/**
	 * Instance du server
	 */
	static PolypeerServer* instance;
	
	/**
	 * Permet de savoir si le serveur est en mode de fonctionnement ou pas.
	 */
	bool running;
	
};


#endif //POLYPEERSERVER_H
