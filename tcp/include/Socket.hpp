#ifndef SOCKET_H
#define SOCKET_H
#include "BaseSocket.hpp"



/**
 * Classe Socket
 * Permet de se connecter à un serveur tcp pour communiquer.
 * Hérite de BaseSocket
 */
class Socket: public BaseSocket
{
public:

	/**
	 * Constructeur d'une Socket vierge qu'il faudra connecter avec la méthode connect()
	 */
	Socket();

	/**
	 * Constructeur qui connecte automatiquement à l'adresse ip et au port concerné
	 * @param char*
	 * addresse ip de la machine cible forma: "192.168.1.1"
	 * @param int
	 * port sur lequel la socket va essayer de se connecter
	 */
	Socket(char* address, int port);

	/**
	 * Contructeur d'une socket déjà connecté grâce à l'identifiant (système) de cette socket
	 * @param int
	 * identifiant de la socket dont on veut créer un objet Socket
	 */
	Socket(int descripteur);
	/**
	 * Destructeur de Socket
	 * Déconnecte la socket (voir destructeur BaseSocket)
	 */
	~Socket();

	/**
	 * Permet de se connecrer à une cible si cele n'a pas té fait à la création ou si on veut changer de cible (penser à utiliser close() avant pour le dernier cas)
	 * @param char*
	 * addresse ip de la machine cible forma: "192.168.1.1"
	 * @param int
	 * port sur lequel la socket va essayer de se connecter
	 */
	void connect(char* address, int port);

	/**
	 * Pour envoyer des données par la Socket. La Socket doit être connecté avant.
	 * @param char*
	 * chaîne de caractères à envoyer à la cible
	 */
	void send(const char* data);

	/**
	 * Permet de lire des données reçues. Fonction bloquante.
	 * @param char*
	 * tableau de caractère déjà alloué de taille sizeBuffer qui va recevoir les données envoyé par l'entité connectée.
	 * @param int
	 * taille maximal de donnée à lire (taille du tableau allouer en 1er paramètre)
	 */
	int read(char* buffer, int sizeBuffer);
};


#endif // SOCKET_H
