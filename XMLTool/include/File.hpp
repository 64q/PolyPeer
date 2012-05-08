#ifndef __H__FILE__
#define __H__FILE__

#include <set>
#include "Entity.hpp"
#include <iostream>

class Entity;

using namespace std;

class File
{

public :
	File(int id, string path, int size, int chunkSize);
	~File();
	int getId() { return id; }
	string getFilePath() { return filePath; }
	int getSize() { return size; }
	int getChunkSize() { return chunkSize; }
	vector<Entity*>* getDeploysOn() { return &deploysOn; }
	void addEntity(Entity* entity);
	
protected :
	int id;
	string filePath;
	int size;
	int chunkSize;
	vector<Entity*> deploysOn;
	
};

#endif


