#ifndef __H__FILE__
#define __H__FILE__

#include <set>
#include <iostream>
#include <ctime>

#include <Entity.hpp>
#include <State.hpp>
#include <FileManager.hpp>
#include <State.hpp>

  /**
	*	Classe contenant les informations d'un déploiement
	*/
	
class Entity;

class File
{

public :

	File(int id, std::string name, std::string serverPath, std::string clientPath);
	File(int id, std::string name, std::string serverPath, std::string clientPath, int chunkSize);
	File(int id, std::string name, std::string serverPath, std::string clientPath, int chunkSize, FileState fs, long dateFile);
	~File();
	std::string getName() { return name; }
	FileManager* getFileManager() { return fileM; }
	FileState getFileState() { return fState; }
	std::string getClientPath() { return clientPath; }
	long getDate() { return date; }
	void setFileState(FileState fs);
	std::vector<Entity*>* getDeploysOn() { return &deploysOn; }
	std::vector<std::vector<Entity*>* >* getSortedHosts();
	static void deleteSortedHost(std::vector<std::vector<Entity*>* >* v);
	void addEntity(Entity* entity);
	Entity* getEntity(std::string name);
	
protected :
	
	time_t date;
	std::string name;
	std::string clientPath;
	FileManager* fileM;
	FileState fState;
	std::vector<Entity*> deploysOn;
	
};

#endif


