#ifndef CHUNK_H
#define CHUNK_H
#include <sstream>
#include <string>
#include <md5.hpp>
#include <Data.hpp>

/**
 * Classe gérant les morceaux de fichiers qui vont être envoyés par socket.
 * Les Chunks sont crées par le FileManager du fichier correspondant.
 * Les Chunks sont serialisables pour permettre l'envoi par socket.
 * @see FileManager
 */


class Chunk
{
public:

	/**
	 * Constructeur initialisant un Chunk.
	 * On peut vérifier la validité du Chunk crée avec la fonction isIntegrate()
	 * @param long
	 * numéro du chunk dans le fichier
	 * @param long
	 * nombre d'octet du chunk (donc taille de data)
	 * @param char*
	 * donnée du chunk
	 * @param int
	 * id du fichier (correspondant à celui enregistré dans le fichier de déploiement XML)
	 * @param char*
	 * code md5 correspondant normalement à data
	 */
	Chunk(long number, long size, char* data, int idFile, char* crc);

	/**
	 * Constructeur qui ne vérifie pas l'intégrité du chunk.
	 * A n'utiliser que si on est sûr du Chunk (si il a été lu dans le fichier)
	 * idem constructeur 1
	 */
	Chunk(long number, long size, char* data, int idFile);

	/**
	 * Constructeur permettant la reconstruction à partir d'un Chunk sérialisé.
	 * @param char*
	 * Chunk sérialisé.
	 */
	Chunk(char* serializedChunk, int);

	/**
	 * Constructeur permettant la reconstruction à partir d'un Chunk sérialisé enveloppé dans un Data.
	 * @param Data
	 * Chunk sérialisé.
	 */
	Chunk(Data& d);
	virtual ~Chunk();

	/**
	 * récupérer les données du chunk.
	 * @return char*
	 * chaine contenant le morceau du fichier correspondant au Chunk.
	 */
	char* getData();

	/**
	 * @return long
	 * taille du chunk en octet (taille du tableau renvoyé par getData()
	 */
	long getSize();


	/**
	 * @return long
	 * numéro du chunk dans le fichier
	 */
	long getNumber();

	/**
	 * @return long
	 * code md5 correspondant à data
	 */
	char* getMD5();

	/**
	 * Indique si le code crc rentré dans le constructeur correspond au code calculé de data.
	 * @return bool
	 * True si le Chunk est correct. Faux si il est incorrect et doit être redemandé au serveur.
	 */
	bool isIntegrate();

	/**
	 * @return int
	 * id du fichier correspondant à celui enregistré dans le fichier de déploiement
	 */
	int getIdFile();

	/**
	 * Permet de récupérer le chunk sous forme sérialisée pour l'envoi par socket.
	 * @param int&
	 * la taille de la chaine de caractère renvoyé est indiqué dans cette variable.
	 * @return char*
	 * chunk sérialisé
	 */
	char* serialize(int& size);


	/**
	 * Permet de récupérer le chunk sous forme sérialisée pour l'envoi par socket.
	 * @return Data
	 * chunk sérialisé
	 */
	Data serialize();

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
