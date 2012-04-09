#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "../include/FileManager.hpp"

using namespace std;

FileManager::FileManager(char* path, long size, long sizeChunk):sizeChunk(sizeChunk)
{
	//on r�serve l'emplacement du fichier sur le disque dur si il n'existe pas encore
	if (!existFile(path))
	{
		reserveFile(path, size);
	}

	//on ouvre le fichier en mode binaire
	file.open(path,ios::binary|ios::in|ios::out|ios::ate);
	if (!file)
	{
		cout<<"probl�me fichier "<<path<<endl;
	}

	//le curseur est � la fin donc la position du curseur donne la taille du fichier
	sizeFile = file.tellp();

	string pathStr(path);
	pathStr += ".STATE";

	pathFileState.assign(pathStr);

	//on v�rifi si le fichier d'enregistrement de l'�tat existe
	ifstream test(pathStr.c_str());
	if (test.fail())
	{
		//si non, on le cr�e et on l'initialise � 0
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
	
	//on remplie le fichier avec des '6' => un caract�re = 1 octet
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
		return Chunk(number, sizeFile-number*sizeChunk, currentData);
	}
	else
	{
		return Chunk(number, sizeChunk, currentData);
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
	//formule de la division arrondie � l'entier sup�rieur
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
