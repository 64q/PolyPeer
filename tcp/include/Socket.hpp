#ifndef SOCKET_H
#define SOCKET_H
#include <BaseSocket.hpp>
#include <Data.hpp>

#include <string>



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
	 * @throw HostNotFoundException, ConnectionException
	 */
	Socket(std::string adress, int port);

	/**
	 * Contructeur d'une socket déjà connecté grâce à l'identifiant (système) de cette socket
	 * @param int
	 * identifiant de la socket dont on veut créer un objet Socket
	 * @param std::string
	 * adresse ip de la Socket sous forme de chaîne de cractère
	 */
	Socket(int descripteur, std::string ipAdress);
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
	 * @throw HostNotFoundException, ConnectionException
	 */
	void connect(std::string address, int port);

	/**
	 * Pour envoyer des données par la Socket. La Socket doit être connecté avant.
	 * @param char*
	 * chaîne de caractères à envoyer à la cible
	 * @param int
	 * taille de la chaine de caractère
	 * @return bool
	 * true si l'envoie s'est bien passé, false sinon
	 */
	bool send(const char* data, int size);

	/**
	 * Pour envoyer des données par la Socket. La Socket doit être connecté avant.
	 * @param const Data&
	 * Data contenant les données à envoyer.
	 * @return bool
	 * true si l'envoie s'est bien passé, false sinon
	 */
	bool send(const Data& data);

	/**
	 * Permet de lire des données reçues. Fonction bloquante.
	 * @param char*
	 * tableau de caractère déjà alloué de taille sizeBuffer qui va recevoir les données envoyé par l'entité connectée.
	 * @param int
	 * taille maximal de donnée à lire (taille du tableau allouer en 1er paramètre)
	 * @return int
	 * taille de la chaîne de caractères lue. -1 si la lecture s'est mal passée.
	 */
	int read(char* buffer, int sizeBuffer);

	std::string getIpAdress();

	void manageWaitingTimeWithPacketState(bool stateValid);


protected:
	std::string ipAdress;
	unsigned int timeWaitForMTUInMc;
	unsigned int numberPacketInvalid;
	unsigned int numberPacketValid;
};


#endif // SOCKET_H
