#ifndef POLYPEERSERVER_H
#define POLYPEERSERVER_H


//#include <Logger.hpp>


class PolypeerServer //: public BaseServer
{
public:
	/**
	 * Démarrage du serveur
	 */
	void start();
	
	/**
	 * Arrêt du serveur
	 */
	void stop();
	
	/**
	 * Restart du serveur
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
	 * Lancement du serveur
	 */
	void run();
	
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
