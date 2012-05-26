#ifndef __H__FILE__
#define __H__FILE__

#include <set>
#include <iostream>

#include <Entity.hpp>
#include <FileManager.hpp>

class Entity;

using namespace std;

class File
{

public :
	File(int id, string name, string path);
	File(int id, string name, string path, int size, int chunkSize);
	~File();
	string getName() { return name; }
	FileManager* getFileManager() { return fileM; }
	vector<Entity*>* getDeploysOn() { return &deploysOn; }
	vector<vector<Entity*>* >* getSortedHosts();

	void addEntity(Entity* entity);
	
protected :
	
	string name;
	FileManager* fileM;
	vector<Entity*> deploysOn;
	
};

#endif


