#ifndef WAITINGPACKETS_H
#define WAITINGPACKETS_H

#include <list>

#include <Packet.hpp>

/**
 * Classe contenant les paquets reçus par les sockets contenus dans le ConectionManager.
 * L'objet doit être unique et sera une ressource partagé.
 */


class WaitingPackets
{
	private:
		/**
		 * L'implémenation de la liste d'attente utilise une liste.
		 * Cela permet d'ajouetr à la fin et de lier le début.
		 */
		list<Packet> packets;

	public:
		/**
		 * Pour ajouter un paquet reçu à la liste d'attente.
		 * @param char*
		 * chaîne de caractères contenant les données reçues.
		 * @param int
		 * taille de la chaine de caractère
		 */
		void push(char* data, int size);

		/**
		 * Permet de récupérer le paquet récupéré en premier.
		 * @return Packet
		 * paquet stocké en tête de liste.
		 */
		Packet get();

		/**
		 * Indque si la liste est vide ou non.
		 * @return bool
		 * True sil la vide est vide. False sinon.
		 */
		bool empty();



};

#endif
