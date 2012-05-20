#ifndef __H_SERVER__
#define __H_SERVER__

#include <map>

#include <BaseServer.hpp>
#include <WebServer.hpp>
#include <Host.hpp>

/**
 * Le serveur principal de l'application PolyPeer. Il s'occupe de gérer les
 * clients et les déploiements.
 */
class Server : public BaseServer
{
public:
	/**
	 * @see BaseServer
	 */
	void start(const int port);
	
	/**
	 * @see BaseServer
	 */
	void stop();
	
	/**
	 * @see BaseServer
	 */
	void restart();
	
	/**
	 * Méthode statique pour récupérer l'instance du Singleton
	 */
	static Server* getInstance();
	
	/**
	 * Récupère une entité via son nom
	 * @param string name
	 * 	nom de l'entité à récupérer
	 */
	Entity getEntity(std::string name);
	
	/**
	 * Destructeur du server
	 */
	virtual ~Server();

private:
	/**
	 * Constructeur du serveur privé (singleton)
	 */
	Server();
	
	/**
	 * @see BaseServer
	 */
	void run();
	
	/**
	 * Instance du serveur
	 */
	static Server* instance;
	
	/**
	 * Pointeur vers le WebServer (singleton)
	 */
	WebServer* webserver;
	
	/**
	 * Map contenant l'ensemble des entitées du réseau
	 */
	std::map<std::string, Entity> entities;
};

#endif
