#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "BaseSocket.hpp"
#include "Socket.hpp"

/**
 * Classe qui permet l'écoute de connexions tcp entrantes.
 * On choisit un port d'écoute grace au constructeur puis on récupère les connexions entrantes
 * grace à la fonction accept() qui va renvoyer une socket permettant de communiquer avec l'ordinateur connecté.
 *
 * Hérite de BaseSocket.
**/

class ServerSocket : public BaseSocket
{
private:
	/**
	 * le port d'écoute du Serversocket
	 */
	int port;

public:
	/**
	 * Constructeur de ServerSocket
	 * @param port
	 * initialisation de l'écoute sur le port concerné
	 */
	ServerSocket(int port);

	/**
	 * Destructeur de Serversocket (voir destructeur BaseSocket)
	 */
	~ServerSocket();

	/**
	 * Méthode bloquante permettant la réception des connexions entrantes.
	 * La méthode bloquera l'exécution du reste du code jusqu'à ce qu'elle reçoive une connexion.
	 * Elle renverra alors une socket permettant de recevoir des données et renvoyer des données à l'entité qui a demandé la connexion.
	 * @return Socket
	 * objet permetant de communiquer avec l'entité qui a demandé la connexion.(voir Socket)
	 */
	Socket* accept();
};

#endif // SERVERSOCKET_H
