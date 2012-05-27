#ifndef __H__XMLTOOL__
#define __H__XMLTOOL__

#include <string>
#include <iostream>
#include <map>
#include <list>

#include <tinyxml/tinyxml.h>
#include <Entity.hpp>
#include <Zone.hpp>
#include <Host.hpp>
#include <File.hpp>
#include <ServerData.hpp>

class ServerData;

class XMLTool 
{
	
public :
	XMLTool(ServerData* sData);
	~XMLTool();
	XMLTool& operator=(XMLTool& reader); 
	
	//Fonctions conteneurs
	void public_displayTopology();
	void writeFileIntoDeployments(File* file);
	void writeEntityIntoFile(int fileId, Entity* entity);
	void removeDeployment(int id);
	int getCurrentId();
	
protected :
	std::string topologyFile;
	std::string deploymentsFile;
	TiXmlDocument DOMTopology;
	TiXmlDocument DOMDeployments;
	
private :
	void displayTopology(TiXmlNode* node, int level = 0);
	void readTopology(ServerData* sData, TiXmlNode* node, std::map<std::string, Entity*>* entities, Entity* parent);
	void readDeployments(ServerData* sData, TiXmlNode* node);
	
};



#endif
