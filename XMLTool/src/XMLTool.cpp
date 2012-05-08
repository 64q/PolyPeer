#include "../include/XMLTool.hpp"


XMLTool::XMLTool()
{
	topologyFile = "";
	deploymentsFile = "";
	DOMTopology = NULL;
	DOMDeployments = NULL;
}

XMLTool::XMLTool(char* topologyName, char* deploymentsName)
{
	topologyFile = string(topologyName);
	deploymentsFile = string(deploymentsName);
	TiXmlDocument DOMT(topologyFile);
	TiXmlDocument DOMD(deploymentsFile);
	DOMTopology = DOMT;
	DOMDeployments = DOMD;
	
	if(!DOMTopology.LoadFile())
		cout << "Erreur lors du chargement du fichier : " << topologyFile << endl;
	if(!DOMDeployments.LoadFile())
		cout << "Erreur lors du chargement du fichier : " << deploymentsFile << endl;
	
	//Création de la topologie dans la map
	readTopology(DOMTopology.RootElement(), getEntities());
	//Ajout des états de déploiement dans la map
	readDeployments(DOMDeployments.RootElement());

}

XMLTool::~XMLTool()
{
	//deleteMap(this->getEntities());
}

void XMLTool::deleteMap(map<string, Entity*>* entities)
{
	map<std::string,Entity*>::iterator
	mit (entities->begin()),
	mend(entities->end());
	map<std::string,Entity*>::iterator tmpIt;
	
	while (mit != mend)
	{
		if (mit->second != NULL)	
		{	
			cout << mit->second->getName() << endl;
			if (mit->second->getEntities() != NULL)
			{
				deleteMap(mit->second->getEntities());
				delete(mit->second);
				entities->erase(mit);
				mit++;
			} else
			{
				delete(mit->second);
				entities->erase(mit);
				mit++;
			}
		}		
	}
}

XMLTool& XMLTool::operator=(XMLTool& r)
{
}

map<string, Entity*>* XMLTool::getEntities()
{
	return &entities;
}

vector<File*>* XMLTool::getDeployFiles()
{
	return &deployFiles;
}

void XMLTool::addFile(int id, string path, int size, int chunkSize)
{
	deployFiles.push_back(new File(id,path,size,chunkSize));
}

File* XMLTool::getFile(int id)
{
	int i=0;
	bool find = false;
	File* toReturn = NULL;

	while( (i < deployFiles.size()) && (find == false) )
	{
		if (deployFiles[i]->getId() == id )
		{
			find = true;
			toReturn = deployFiles[i];
		}
		i++;
	}
	return toReturn;	
}

void XMLTool::displayTopology(TiXmlNode* node, int level)
{
	cout << string( level*3, ' ' ) << "<" << node->Value() << "> ";
	if ( node->ToElement() )
	{
		TiXmlElement* elem = node->ToElement();
		for ( const TiXmlAttribute* attr = elem->FirstAttribute(); attr; attr = attr->Next() )
		cout << " (" << attr->Name() << "=" << attr->Value() << ")";
	}
	cout << "\n";

	for(TiXmlNode* element = node->FirstChild(); element; element = element->NextSibling())
		displayTopology( element, level + 1 );
}

void XMLTool::readTopology(TiXmlNode* node, map<string, Entity*>* entities)
{
	int id;
	Zone* zone = NULL;
	Entity* entity = NULL;
	
	if ( node->ToElement() )
	{
		TiXmlElement* elem = node->ToElement();
		if (!(node->ValueStr().compare("host")))
		{
			if (elem->Attribute("ref") != NULL )
			{
				entity = getEntity(getEntities(), elem->Attribute("ref"));
				if (entity != NULL)
					entities->insert(make_pair(elem->Attribute("ref"), entity));
				else 
					cout << "reference inexistante" << endl;
			}else
			{
				entities->insert(make_pair(elem->Attribute("name"), new Host(elem->Attribute("name"), elem->Attribute("address"))));
			}
		}
		if (!(node->ValueStr().compare("zone")))
		{
			if (elem->Attribute("ref") != NULL )
			{
				entity = getEntity(getEntities(), elem->Attribute("ref"));
				if (entity != NULL)
					entities->insert(make_pair(elem->Attribute("ref"), entity));
				else 
					cout << "reference inexistante" << endl;
			}else
			{
				zone = new Zone(elem->Attribute("name"));
				entities->insert(make_pair(elem->Attribute("name"), zone));
			}
		}
	} 
	

	for(TiXmlNode* element = node->FirstChild(); element; element = element->NextSibling())
	{
		if ( node->ToElement() )
		{
			if (!(node->ValueStr().compare("zone")))
				readTopology(element, zone->getEntities());
			else 
				readTopology(element, entities);
		}
	}
}

void XMLTool::readDeployments(TiXmlNode* node)
{
	int id = 0;
	int size = 0;
	int chunkSize = 0;
	Entity* entity = NULL;
	
	if ( node->ToElement() )
	{
		TiXmlElement* parentElem = (node->Parent())->ToElement();
		TiXmlElement* elem = node->ToElement();
		if (!(node->ValueStr().compare("file")))
		{
			elem->QueryIntAttribute("id", &id);
			elem->QueryIntAttribute("size", &size);
			elem->QueryIntAttribute("chunkSize", &chunkSize);
			addFile(id,elem->Attribute("path"), size, chunkSize);
		}
		if (!(node->ValueStr().compare("zone")) || !(node->ValueStr().compare("host")))
		{
			entity = getEntity(getEntities(), elem->Attribute("ref"));
			if (entity != NULL)
			{
				parentElem->QueryIntAttribute("id", &id);
				fillDeploymentStates(entity, id);
			}
		}	
	} 
	

	for(TiXmlNode* element = node->FirstChild(); element; element = element->NextSibling())
	{
		if ( node->ToElement() )
			readDeployments(element);
	}
}

void XMLTool::displayEntities(map<string, Entity*>* entities, int level)
{
	int i;
	map<std::string,Entity*>::const_iterator
	mit (entities->begin()),
	mend(entities->end());
		
	for(; mit!=mend; ++mit) 
	{
		cout << string( level*3, ' ' ) << mit->first << " ";		
		if (mit->second->getEntities() != NULL)
		{
			cout << endl;
			displayEntities(mit->second->getEntities(), level + 1);
		}
		if (mit->second->getDeploys() != NULL)
		{
			if (!((mit->second->getDeploys())->empty()))
			{
				for (i=0; i < (mit->second->getDeploys())->size(); i++)
				{
					cout << " | fID : " << (((*(mit->second->getDeploys()))[i]).getRefFile())->getId();
					cout << " | cID : " << (*(mit->second->getDeploys()))[i].getCurrentIdChunk();
					cout << " | fPath : " << ((*(mit->second->getDeploys()))[i].getRefFile())->getFilePath();
					cout << " | hState : " << (*(mit->second->getDeploys()))[i].getCurrentState();
					cout << endl;
					cout << string( level*3 + (mit->first).size(), ' ' ) << " " ;
				}
			}
		}
		cout << endl;
		
	}
}

Entity* XMLTool::getEntity(map<string, Entity*>* entities, string entityName)
{
	Entity* toReturn = NULL;
	map<std::string,Entity*>::const_iterator
	mit (entities->begin()),
	mend(entities->end());
	
	for(; mit!=mend; ++mit) 
	{	
		if (toReturn == NULL)
		{
			if (!((mit->second->getName()).compare(entityName)))
				toReturn = mit->second;
			else if (mit->second->getEntities() != NULL)	
				toReturn = getEntity(mit->second->getEntities(), entityName);
		}
	}

	return toReturn;
}

void XMLTool::fillDeploymentStates(Entity* entity, int fileID)
{
	map<string, Entity*>* entities;
	File* file;
	
	if (entity != NULL)
	{
		entities = entity->getEntities();
		if ( entities != NULL)
		{
			map<std::string,Entity*>::const_iterator
			mit (entities->begin()),
			mend(entities->end());
			for(; mit!=mend; ++mit) 
			{	
				if (mit->second->getIP() != NULL)
				{
					file = getFile(fileID);
					file->addEntity(mit->second);
					mit->second->addDeploymentState(0, file, WAIT);
				}
				if (mit->second->getEntities() != NULL)
					fillDeploymentStates(mit->second, fileID);
			}
		} else 
		{
			file = getFile(fileID);
			file->addEntity(entity);
			entity->addDeploymentState(0, file, WAIT);
		}
	}
}

void XMLTool::fillAddressList(Entity* entity, list<string> &list)
{ 
	map<string, Entity*>* entities;
	if (entity != NULL)
	{
		entities = entity->getEntities();
		if ( entities != NULL)
		{
			map<std::string,Entity*>::const_iterator
			mit (entities->begin()),
			mend(entities->end());
			for(; mit!=mend; ++mit) 
			{	
				if (mit->second->getIP() != NULL)
					list.push_back(*(mit->second->getIP()));
				if (mit->second->getEntities() != NULL)
					fillAddressList(mit->second, list);
			}
		} else 
			list.push_back(*(entity->getIP()));
	}
}

void XMLTool::public_displayTopology() 
{ 
	displayTopology(DOMTopology.RootElement()); 
}

void XMLTool::public_displayEntities() 
{ 
	displayEntities(getEntities()); 
}

Entity*XMLTool::public_getEntity(string entityName) 
{ 
	getEntity(&entities, entityName); 
}

void XMLTool::public_fillAddressList(string entityName, list<string> &list) 
{
	Entity* entity;
	entity = getEntity(&entities, entityName);
	fillAddressList(entity, list); 
}

