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

using namespace std;


class XMLTool 
{
	
public :
	~XMLTool();
	XMLTool& operator=(XMLTool& reader); 
	
	static XMLTool* getInstance();
	//Fonctions conteneurs
	void public_displayTopology();
	
protected :
	static XMLTool* instance; 
	string topologyFile;
	string deploymentsFile;
	TiXmlDocument DOMTopology;
	TiXmlDocument DOMDeployments;
	
private :
	XMLTool();
	void displayTopology(TiXmlNode* node, int level = 0);
	void readTopology(TiXmlNode* node, map<string, Entity*>* entities);
	void readDeployments(TiXmlNode* node);
	
};



#endif
