#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <FileManager.hpp>

using namespace std;

FileManager::FileManager(char* path, long size, long sizeChunk, int idFile):sizeChunk(sizeChunk), idFile(idFile)
{
	//on réserve l'emplacement du fichier sur le disque dur si il n'existe pas encore
	if (!existFile(path))
	{
		reserveFile(path, size);
	}

	//on ouvre le fichier en mode binaire
	file.open(path,ios::binary|ios::in|ios::out|ios::ate);
	if (!file)
	{
		cout<<"problème fichier "<<path<<endl;
	}

	//le curseur est à la fin donc la position du curseur donne la taille du fichier
	sizeFile = file.tellp();

	string pathStr(path);
	pathStr += ".STATE";

	pathFileState.assign(pathStr);

	//on vérifi si le fichier d'enregistrement de l'état existe
	ifstream test(pathStr.c_str());
	if (test.fail())
	{
		//si non, on le crée et on l'initialise à 0
		ofstream tmp(pathStr.c_str());
		tmp << 0;
		tmp.close();
	}

	currentData = new char[sizeChunk];
}

bool FileManager::existFile(char* path)
{
	ifstream fichier(path);
	return !fichier.fail();
}

void FileManager::reserveFile(char* path, long size)
{
	ofstream create(path, ios::out|ios::app);

	//on remplie le fichier avec des '6' => un caractère = 1 octet
	for (int i = 0; i < size; i++)
	{
		create<<'6';
	}

	create.close();
}

FileManager::~FileManager()
{
	file.close();
	delete [] currentData;
}

Chunk FileManager::getChunk(long number)
{
	file.seekp(number*sizeChunk, ios::beg);
	file.read(currentData, sizeChunk);

	if (getNumberChunk()-1==number)
	{
		return Chunk(number, sizeFile-number*sizeChunk, currentData, idFile);
	}
	else
	{
		return Chunk(number, sizeChunk, currentData, idFile);
	}
}
bool FileManager::saveChunk(Chunk &chunk)
{
	currentChunk = getState();

	if (currentChunk == chunk.getNumber())
	{
		file.seekp(currentChunk*sizeChunk, ios::beg);
		file.write(chunk.getData(), chunk.getSize());

		currentChunk++;
		saveState();

		return true;
	}
	else
	{
		return false;
	}
}

long FileManager::getNumberChunk()
{
	//formule de la division arrondie à l'entier supérieur
	return (sizeFile+sizeChunk-1)/sizeChunk;
}

long FileManager::getState()
{
	ifstream tmp(pathFileState.c_str());
	int i;
	tmp >> i;
	tmp.close();

	return i;
}
void FileManager::saveState()
{
    ofstream tmp(pathFileState.c_str(), ios::trunc);
    tmp << currentChunk;
    tmp.close();

}

long FileManager::getFileSize()
{
    return sizeFile;
}













