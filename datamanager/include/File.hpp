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

	File(int id, std::string name, std::string path);
	File(int id, std::string name, std::string path, int size, int chunkSize);
	File(int id, std::string name, std::string path, int size, int chunkSize, FileState fs);
	~File();
	std::string getName() { return name; }
	FileManager* getFileManager() { return fileM; }
	FileState getFileState() { return fState; }
	void setFileState(FileState fs);
	std::vector<Entity*>* getDeploysOn() { return &deploysOn; }
	std::vector<std::vector<Entity*>* >* getSortedHosts();
	static void deleteSortedHost(std::vector<std::vector<Entity*>* >* v);
	void addEntity(Entity* entity);
	Entity* getEntity(int id);
	
protected :
	
	std::string name;
	FileManager* fileM;
	FileState fState;
	std::vector<Entity*> deploysOn;
	
};

#endif


