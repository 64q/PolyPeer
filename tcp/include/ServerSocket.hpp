#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "BaseSocket.hpp"
#include "Socket.hpp"

/**
 * Classe qui permet l'�coute de connexions tcp entrantes.
 * On choisit un port d'�coute grace au constructeur puis on r�cup�re les connexions entrantes
 * grace � la fonction accept() qui va renvoyer une socket permettant de communiquer avec l'ordinateur connect�.
 *
 * H�rite de BaseSocket.
**/

class ServerSocket : public BaseSocket
{
private:
	/**
	 * le port d'�coute du Serversocket
	 */
	int port;

public:
	/**
	 * Constructeur de ServerSocket
	 * @param port
	 * initialisation de l'�coute sur le port concern�
	 */
	ServerSocket(int port);

	/**
	 * Destructeur de Serversocket (voir destructeur BaseSocket)
	 */
	~ServerSocket();

	/**
	 * M�thode bloquante permettant la r�ception des connexions entrantes.
	 * La m�thode bloquera l'ex�cution du reste du code jusqu'� ce qu'elle re�oive une connexion.
	 * Elle renverra alors une socket permettant de recevoir des donn�es et renvoyer des donn�es � l'entit� qui a demand� la connexion.
	 * @return Socket
	 * objet permetant de communiquer avec l'entit� qui a demand� la connexion.(voir Socket)
	 */
	Socket* accept();
};

#endif // SERVERSOCKET_H
