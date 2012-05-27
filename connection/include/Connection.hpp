#ifndef CONNECTION_H
#define CONNECTION_H
#include <Socket.hpp>
#include <pthread.h>
#include <vector>



/**
 * Classe servant à lancer dans un thread qui va écouter la socket pour ajouter les paquets reçus
 * dans la WaitingPacket. Les Connection sont gérées par de le ConnectionManager.
 * @see WaitingPacket
 * @see ConnectionManager
 */


class Connection
{
	public:
		/**
		 * Constructeur unique.
		 * @param Socket*
		 * pointeur de la Socket dont l'écoute va être lancé dans un thread.
		 * @param WaitingPacket*
		 * Pointeur vers l'instance de WaitingPacket où les paquets reçus vont être stockés.
		 */
		Connection(Socket* socket);

		virtual ~Connection();

		/**
		 * Lance le thread d'écoute.
		 */
		void start();

		/**
		 * Arrête le thread proprement.
		 */
		void stop();

		/**
		 * Permet de récupérer la Socket qui est en écoute (pour envpyer un paquet par exemple.
		 * Ne pas utiliser pour écouter la socket, les messages reçus sont stocké dans WaitingPacket.
		 * @return Socket*
		 * La socket en écoute.
		 */
		Socket* getSocket();

		void throwUpdatePacket();

	private:
		Socket* socket;
		std::string name;
		pthread_t thread;
		bool run;


		//les pthreads ne peuvent pas prendre une méthode en paramètre.
		//obligé d'utiliser une fonction extérieur
		friend void* listenSocket(void* connection);


};

#endif // CONNECTION_H
