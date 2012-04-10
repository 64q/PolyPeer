#ifndef SOCKET_H
#define SOCKET_H
#include "BaseSocket.hpp"



/**
 * Classe Socket
 * Permet de se connecter � un serveur tcp pour communiquer.
 * H�rite de BaseSocket
 */
class Socket: public BaseSocket
{
public:

	/**
	 * Constructeur d'une Socket vierge qu'il faudra connecter avec la m�thode connect()
	 */
	Socket();

	/**
	 * Constructeur qui connecte automatiquement � l'adresse ip et au port concern�
	 * @param char*
	 * addresse ip de la machine cible forma: "192.168.1.1"
	 * @param int
	 * port sur lequel la socket va essayer de se connecter
	 */
	Socket(char* address, int port);

	/**
	 * Contructeur d'une socket d�j� connect� gr�ce � l'identifiant (syst�me) de cette socket
	 * @param int
	 * identifiant de la socket dont on veut cr�er un objet Socket
	 */
	Socket(int descripteur);
	/**
	 * Destructeur de Socket
	 * D�connecte la socket (voir destructeur BaseSocket)
	 */
	~Socket();

	/**
	 * Permet de se connecrer � une cible si cele n'a pas t� fait � la cr�ation ou si on veut changer de cible (penser � utiliser close() avant pour le dernier cas)
	 * @param char*
	 * addresse ip de la machine cible forma: "192.168.1.1"
	 * @param int
	 * port sur lequel la socket va essayer de se connecter
	 */
	void connect(char* address, int port);

	/**
	 * Pour envoyer des donn�es par la Socket. La Socket doit �tre connect� avant.
	 * @param char*
	 * cha�ne de caract�res � envoyer � la cible
	 */
	void send(const char* data);

	/**
	 * Permet de lire des donn�es re�ues. Fonction bloquante.
	 * @param char*
	 * tableau de caract�re d�j� allou� de taille sizeBuffer qui va recevoir les donn�es envoy� par l'entit� connect�e.
	 * @param int
	 * taille maximal de donn�e � lire (taille du tableau allouer en 1er param�tre)
	 */
	int read(char* buffer, int sizeBuffer);
};


#endif // SOCKET_H
