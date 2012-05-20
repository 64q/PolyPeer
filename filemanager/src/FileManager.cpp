#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <FileManager.hpp>

using namespace std;

FileManager::FileManager(const char* path, long size, long sizeChunk, int idFile):idFile(idFile), sizeChunk(sizeChunk)
{
	string pathStrTmp(path);
	pathStrTmp+="";

	//on réserve l'emplacement du fichier sur le disque dur si il n'existe pas encore
	if (!existFile(pathStrTmp.c_str()))
	{
		if(getFreeDiskSpace() >= (unsigned)size)
		{
			reserveFile(pathStrTmp.c_str(), size);
		}else
		{
			//si il n'y a pas assez d'espace libre sur le dd on lance un exception
			throw DiskFullException();
		}

	}

	//on ouvre le fichier en mode binaire
	file.open(pathStrTmp.c_str(),ios::binary|ios::in|ios::out|ios::ate);
	if (!file)
	{
		cout<<"problème fichier "<<pathStrTmp<<endl;
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

bool FileManager::existFile(const char* path)
{
	ifstream fichier(path);
	return !fichier.fail();
}

void FileManager::reserveFile(const char* path, long size)
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


int FileManager::getIdFile()
{
	return idFile;
}

std::string FileManager::getFileName()
{
	int last = pathFileState.find_last_of("/");

	if(last > 0)
	{
		//le 6 correspond au .STATE
		return pathFileState.substr( last,pathFileState.size() - last - 6);
	}

	return pathFileState.substr( 0,pathFileState.size() - 6);

}

long FileManager::getChunkSize()
{
	return sizeChunk;
}

long FileManager::getCurrentNumberChunk()
{
	return currentChunk;
}

int64_t FileManager::getFreeDiskSpace()
{
	 int64_t available;
    #ifdef WIN32
        GetDiskFreeSpaceEx(NULL,(PULARGE_INTEGER)&available,NULL,NULL);
    #elif defined (linux)
        struct statfs sf;
        statfs("./", &sf);
        //f_bavail contient le nombre de blocks disponibles, f_bsize contient la taille d'un block en octet
        available=sf.f_bavail*sf.f_bsize;
    #endif

	return available;
}







