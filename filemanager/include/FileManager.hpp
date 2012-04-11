#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <fstream>
#include <iostream>

#include "../include/Chunk.hpp"

class FileManager
{
public:
	//path: chemin d'acc�s du fichier
	//sizeChunk: taille de chaque Chunk dans lesquels vont �tre plac�s les morceaux du fichier
	FileManager(char* path, long size, long sizeChunk, int idfile);

	virtual ~FileManager();

	//on r�cup�re le Chunk correspondant au number
	Chunk getChunk(long number);

	//on enregistre le Chunk dans le fichier avec les v�rifications n�cessaires
	bool saveChunk(Chunk &chunk);

	//renvoie le nombre de Chunk n�cessaires pour r�cup�rer le fichier entier
	long getNumberChunk();

	//renvoie la taille du fichier charg�
	long getFileSize();



protected:
	std::fstream file;
	int idFile;
	std::string pathFileState;
	char* currentData;
	long currentChunk;
	long sizeFile;
	long sizeChunk;

	long getState();
	void saveState();
	bool existFile(char* path);
	void reserveFile(char* path, long size);
};

#endif // FILEMANAGER_H
