#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <fstream>
#include <iostream>

#include <Chunk.hpp>


#ifdef WIN32 /* si vous êtes sous Windows */
#include <windows.h>



#elif defined (linux) /* si vous êtes sous Linux */
#include <stdint.h>
#include <sys/vfs.h>

#else /* sinon vous êtes sur une plateforme non supportée */

#error not defined for this platform

#endif

/**
 * Classe de gestion des fichiers à déployer
 * Permet de récupérer les morceaux de fichier sous forme de Chunk
 * @see Chunk
 */


class FileManager
{
public:


	/**
	 * Constructeur pour un fichier déjà complet (sur le serveur ou sur un client qui a fini de dl un fichier).
	 * @param const char*
	 * chemin d'accès du fichier
	 * @param int
	 * id du fichier (renseigné dans le fichier XML de déploiement)
	 * @param long
	 * taille de chaque Chunk dans lesquels vont être placés les morceaux du fichier
	 */
	FileManager(const char* path, int idFile, long sizeChunk=5800);

	/**
	 * Constructeur pour un fichier incomplet ou dont on ignore l'état.
	 * @param const char*
	 * chemin d'accès du fichier
	 * @param long
	 * taille du fichier (utile seulement si le fichier n'existe pas déjà)
	 * @param long
	 * taille de chaque Chunk dans lesquels vont être placés les morceaux du fichier
	 * @param int
	 * id du fichier (renseigné dans le fichier XML de déploiement)
	 */
	FileManager(const char* path, long size, long sizeChunk, int idfile);

	virtual ~FileManager();

	/**
	 * On récupère le Chunk correspondant au number
	 * @param long
	 * numéro du Chunk que l'on veut récupérer (doit être inférieur à la valeur retournée par getNumberChunk() )
	 */
	Chunk* getChunk(long number);

	/**
	 * On enregistre le Chunk dans le fichier avec les vérifications nécessaires
	 * @param Chunk
	 * Chunk qui va être enregistré dans le fichier si il correspond à celui attendu (les Chunk doivent être enregistrés dans l'ordre)
	 * @return bool
	 * True si le Chunk est bien enregistré, False si il y a eu un problème
	 */
	bool saveChunk(Chunk &chunk);

	/**
	 * Renvoie le nombre de Chunk nécessaires pour récupérer le fichier entier
	 * @return long
	 * nombre de Chunk contenu dans le fichier
	 */
	long getNumberChunk();

	/**
	 * Renvoie la taille du fichier chargé
	 * @return long
	 * Taille en octet du fichier chargé
	 */
	long getFileSize();

	/**
	 * Renvoie l'id du fichier
	 * @return int
	 * id du fichier (renseigné dans le fichier XML de déploiement)
	 */
	int getIdFile();

	/**
	 * Renvoie le nom du fichier
	 * @return string
	 * Nom du fichier sans le chemin d'accès
	 */
	std::string getFileName();

	std::string getFilePath();

	/**
	 * Renvoie la taille des Chunk(s) crées
	 * @return long
	 * taille des Chunk qui vont être générés
	 */
	long getChunkSize();

	/**
	 * Renvoie le numéro du Chunk qui est attendu.
	 * @return long
	 * numéro du Chunk qui doit être réceptionné
	 */
	long getCurrentNumberChunk();

	/**
	 * Renvoie la taille disponible sur le disque dur en octet.
	 * @return long
	 * taille disponible sur le disque dur en octet.
	 */
	int64_t getFreeDiskSpace();

protected:
	std::filebuf *pbuf;
	std::fstream file;
	int idFile;
	std::string pathFile;
	std::string pathFileState;
	char* currentData;
	long currentChunk;
	long sizeFile;
	long sizeChunk;
	bool isComplete;

	void init(const char* path, long size, long sizeChunk, int idFile);
	long getState();
	void saveState();
	bool existFile(const char* path);
	void reserveFile(const char* path, long size);
	void setCompleted();
	void checkDirectory(std::string pathDirectory);
	void createDirectory(std::string pathDirectory, std::string currentPath);
};

#endif // FILEMANAGER_H

