#ifndef CHUNK_H
#define CHUNK_H
#include <sstream>
#include <string>
#include "md5.hpp"

class Chunk
{
public:
	//number: num�ro du chunk dans le fichier
	//size: nombre d'octet du chunk (donc taille de data)
	//data: donn�e du chunk
	//crc: code md5 correspondant normalement � data
	//(valeur test�e par rapport � la valeur th�orique-> r�sultat avec isIntegrate() )
	Chunk(long number, long size, char* data, int idFile, char* crc);
	Chunk(long number, long size, char* data, int idFile);
	Chunk(char* serializedChunk, int);
	virtual ~Chunk();

	//r�cup�rer les donn�es du chunk
	char* getData();

	//taille du chunk en octet (taille du tableau renvoy� par getdate()
	long getSize();

	//num�ro du chunk dans le fichier
	long getNumber();

	//r�cup�rer le code md5 correspondant � data
	char* getMD5();

	//indique si le code crc rentr� dans le constructeur correspond au code calcul� de data
	//si false est renvoy�, le chunk est faux et doit �tre redemand� au serveur
	bool isIntegrate();

	int getIdFile();

	char* serialize(int& size);

protected:
	long number;
	long size;
	char *data;
	char *md5;
	bool chunkIntegrity;
	int idFile;

private:
	static MD5 encoder;
	void initialiser(long number, long size, char* data, int idFile);
	void checkIntegrity(char* crc);

};

#endif // CHUNK_H
