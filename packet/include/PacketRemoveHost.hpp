#ifndef PACKETREMOVEHOST_H
#define PACKETREMOVEHOST_H


/*
 * Classe PacketRemoveHost
 *
 * Hérite de la classe Packet
 * Gérer un type de packet spécifique
 *
 *
 *
 *
 * par Erwan
 */


// Project header
#include <Packet.hpp>



class PacketRemoveHost : public Packet
{
private:


public:
	/**
	* Création d'un PacketRemoveHost pret à être envoyé
	*
	*/
	PacketRemoveHost(std::string ip);

	/**
	* Constructeur sur un Packet (une maniere de caster un Packet)
	*/
	PacketRemoveHost(const Packet& p);

	/**
	* Destructeur
	*/
	virtual ~PacketRemoveHost();

	std::string getIpAddress ();

private:
	PacketRemoveHost() {};

};

#endif // PACKETSENDCHUNK_H
