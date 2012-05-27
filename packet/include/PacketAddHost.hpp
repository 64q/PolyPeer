#ifndef PACKETADDHOST_H
#define PACKETADDHOST_H


/*
 * Classe PacketAddHost
 *
 * Hérite de la classe Packet
 * Gérer un type de packet spécifique
 *
 *
 * par Erwan
 */


// Project class
#include <Packet.hpp>


class PacketAddHost : public Packet
{
private:


public:
	/**
	* Création d'un PacketAddHost pret à être envoyé
	*
	*/
	PacketAddHost(std::string ipAddress);

	/**
	* Constructeur sur un Packet (une maniere de caster un Packet)
	*/
	PacketAddHost(const Packet& p);

	/**
	* Destructeur
	*/
	virtual ~PacketAddHost();

	std::string getIpAddress ();


private:
	PacketAddHost() {}

};

#endif // PACKETCHUNKRECEIVED_H
