#ifndef __H__XMLTOOL__
#define __H__XMLTOOL__

#include <string>
#include <iostream>
#include <map>
#include <list>
#include "tinyxml/tinyxml.h"
#include "Entity.hpp"
#include "Zone.hpp"
#include "Host.hpp"
#include "File.hpp"

using namespace std;

class XMLTool 
{
	
public :
	XMLTool();
	XMLTool(char* topologyName, char* deploymentsName);
	~XMLTool();
	XMLTool& operator=(XMLTool& reader);
	map<string, Entity*>* getEntities();
	vector<File*>* getDeployFiles();
	void addFile(int id, string path, int size, int chunkSize);
	File* getFile(int id); 
	
	//Fonctions conteneurs
	void public_displayTopology();
	void public_displayEntities();
	Entity* public_getEntity(string entityName);
	void public_fillAddressList(string entityName, list<string> &list);
	
protected : 
	string topologyFile;
	string deploymentsFile;
	TiXmlDocument DOMTopology;
	TiXmlDocument DOMDeployments;
	map<string, Entity*> entities;
	vector<File*> deployFiles;
	
private :
	void deleteMap(map<string, Entity*>* entities);
	void displayTopology(TiXmlNode* node, int level = 0);
	void readTopology(TiXmlNode* node, map<string, Entity*>* entities);
	void readDeployments(TiXmlNode* node);
	void displayEntities(map<string, Entity*>* entities, int level = 0);
	Entity* getEntity(map<string, Entity*>* entities, string entityName);
	void fillDeploymentStates(Entity* entity, int fileID);
	void fillAddressList(Entity* entity, list<string> &list);
	
};



#endif
