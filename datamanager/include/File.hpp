#ifndef __H__FILE__
#define __H__FILE__

#include <set>
#include <iostream>

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
	File(int id, std::string name, std::string serverPath, std::string clientPath, int size, int chunkSize);
	File(int id, std::string name, std::string serverPath, std::string clientPath, int size, int chunkSize, FileState fs);
	~File();
	std::string getName() { return name; }
	FileManager* getFileManager() { return fileM; }
	FileState getFileState() { return fState; }
	std::string getClientPath() { return clientPath; }
	void setFileState(FileState fs);
	std::vector<Entity*>* getDeploysOn() { return &deploysOn; }
	std::vector<std::vector<Entity*>* >* getSortedHosts();
	static void deleteSortedHost(std::vector<std::vector<Entity*>* >* v);
	void addEntity(Entity* entity);
	Entity* getEntity(std::string name);
	
protected :
	
	std::string name;
	std::string clientPath;
	FileManager* fileM;
	FileState fState;
	std::vector<Entity*> deploysOn;
	
};

#endif


