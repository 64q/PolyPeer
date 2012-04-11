#ifndef CHUNK_H
#define CHUNK_H
#include <sstream>
#include <string>
#include "md5.hpp"

class Chunk
{
public:
	//number: numéro du chunk dans le fichier
	//size: nombre d'octet du chunk (donc taille de data)
	//data: donnée du chunk
	//crc: code md5 correspondant normalement à data
	//(valeur testée par rapport à la valeur théorique-> résultat avec isIntegrate() )
	Chunk(long number, long size, char* data, int idFile, char* crc);
	Chunk(long number, long size, char* data, int idFile);
	Chunk(char* serializedChunk, int);
	virtual ~Chunk();

	//récupérer les données du chunk
	char* getData();

	//taille du chunk en octet (taille du tableau renvoyé par getdate()
	long getSize();

	//numéro du chunk dans le fichier
	long getNumber();

	//récupérer le code md5 correspondant à data
	char* getMD5();

	//indique si le code crc rentré dans le constructeur correspond au code calculé de data
	//si false est renvoyé, le chunk est faux et doit être redemandé au serveur
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
