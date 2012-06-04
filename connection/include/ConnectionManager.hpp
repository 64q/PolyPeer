#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <map>
#include <string>
#include <vector>
#include <pthread.h>

#include <Connection.hpp>
#include <ServerSocket.hpp>
#include <Packet.hpp>
#include <Mutex.hpp>

/**
 * Classe gérant les sockets d'écoute. Quand un socket est ajouté au connectionManager, il lance l'écoute dans un thread.
 * la classe permet de récupérer les socket qu'il contient par le nom du PC corespondant.
 * Par Erwan
 */


class ConnectionManager
{
	public:
		/**
		 * Constructeur
		 */
		ConnectionManager(int port);
		virtual ~ConnectionManager();

		/**
		 * Permet d'ajouter une connection au manager. Le Manager va lancer l'écoute dans un thread/
		 * @param string
		 * le nom de l'ordinateur connecté sur ce socket
		 * @param Socket*
		 * pointeur vers la socket correspondant au nom et qui va être écouté.
		 */
		void addConnection(std::string name, Socket* socket);

		/**
		 * Permet de récupérer l'instance de connection qui correspond au nom passé en paramètre.
		 * @param string
		 * nom de l'ordinateur dont on veut récupérer la connection
		 * @return Connection*
		 * Pointeur vers la connection correspondante au nom passé en paramètre.
		 */
		Connection* getConnection(std::string name);

		/**
		 * Lance l'écoute des connexions entrantes et l'ajout de ces connexions dans le tableau de Conection dans un thread
		 */
		void start();

		/**
		 * Arrête le thread d'écoute des connexions entrantes et coupe toutes les connexions en cours.
		 * A n'utiliser qu'à la fermeture du programme!
		 */
		void stop();


		void sendTo(std::string dest, Packet packet);

		void wait();

		void removeConnection(std::string);

		static bool WOL(const char *bcastAddr,const char *macAddr="255.255.255.255");


	private:
		std::map<std::string, Connection*> listConnections;


		pthread_t thread;
		bool run;
		ServerSocket* serverSocket;

		Mutex mutex;

		friend void* runFct(void* connectionManager);
};

#endif // CONNECTIONMANAGER_H
