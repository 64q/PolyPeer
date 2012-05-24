#ifndef PACKETNEWFILE_H
#define PACKETNEWFILE_H


/*
 * Classe PacketNewFile
 *
 * Hérite de la classe Packet
 * Gérer un type de packet spécifique
 *
 *
 *
 *
 * par Olivier
 */


// Project header
#include <Packet.hpp>

class PacketNewFile : public Packet
{
private:


public:
	/**
	* Création d'un PacketNewFile pret à être envoyé
	*
	*/
	PacketNewFile(int idFile, std::string fileName, int size, int sizeChunk);

	/**
	* Constructeur sur un Packet (une maniere de caster un Packet)
	*/
	PacketNewFile(const Packet& p);

	/**
	* Destructeur
	*/
	virtual ~PacketNewFile();

	int getIdFile ();

	std::string getFileName ();

	int getFileSize ();

	int getChunkSize();

private:
	PacketNewFile() {}

};

#endif // PACKETNEWFILE_H
