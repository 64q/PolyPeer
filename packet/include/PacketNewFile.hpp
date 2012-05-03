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


// Entêtes
#include <iostream>
#include <Chunk.hpp>

#include <Packet.hpp>

using namespace std;

class PacketNewFile : public Packet
{
private:


public:
	/**
	* Création d'un PacketNewFile pret à être envoyé
	*
	*/
	PacketNewFile(int idFile, string fileName, int size, int sizeChunk);

	/**
	* Constructeur sur un Packet (une maniere de caster un Packet)
	*/
	PacketNewFile(const Packet& p);

	/**
	* Destructeur
	*/
	virtual ~PacketNewFile();

	int getIdFile ();

	string getFileName ();

	int getFileSize ();

	int getChunkSize();

private:
	PacketNewFile() {}

};

#endif // PACKETNEWFILE_H
