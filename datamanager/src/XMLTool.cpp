#include <XMLTool.hpp>


XMLTool::XMLTool(ServerData* sData)
{
	
	topologyFile = string("topology.xml");
	deploymentsFile = string("deployments.xml");
	TiXmlDocument DOMT(topologyFile);
	TiXmlDocument DOMD(deploymentsFile);
	DOMTopology = DOMT;
	DOMDeployments = DOMD;
	
	if(!DOMTopology.LoadFile())
		cout << "Erreur lors du chargement du fichier : " << topologyFile << endl;
	if(!DOMDeployments.LoadFile())
		cout << "Erreur lors du chargement du fichier : " << deploymentsFile << endl;
	
	//Création de la topologie dans la map
	readTopology(sData, DOMTopology.RootElement(), sData->getEntities(), NULL);
	//Ajout des états de déploiement dans la map
	readDeployments(sData, DOMDeployments.RootElement());
}

XMLTool::~XMLTool()
{
	
}

XMLTool& XMLTool::operator=(XMLTool& r)
{
	return *this;
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

void XMLTool::readTopology(ServerData* sData, TiXmlNode* node, map<string, Entity*>* entities, Entity* parent)
{
	Zone* zone = NULL;
	Entity* entity = NULL;
	int capacity;
	
	if ( node->ToElement() )
	{
		TiXmlElement* elem = node->ToElement();
		if (!(node->ValueStr().compare("host")))
		{
			if (elem->Attribute("ref") != NULL )
			{
				entity = sData->getHostByName(elem->Attribute("ref"));
				if (entity != NULL)
					entities->insert(make_pair(elem->Attribute("ref"), entity));
				else 
					cout << "reference inexistante" << endl;
			}else
			{
				elem->QueryIntAttribute("networkCapacity", &capacity);
				entity = sData->addHost(elem->Attribute("name"), parent, capacity, elem->Attribute("address"));
				entities->insert(make_pair(elem->Attribute("name"), entity));
			}
		}
		if (!(node->ValueStr().compare("zone")))
		{
			if (elem->Attribute("ref") != NULL )
			{
				entity = sData->public_getEntity(elem->Attribute("ref"));
				if (entity != NULL)
					entities->insert(make_pair(elem->Attribute("ref"), entity));
				else 
					cout << "reference inexistante" << endl;
			}else
			{
				elem->QueryIntAttribute("networkCapacity", &capacity);
				zone = new Zone(elem->Attribute("name"), parent, capacity);
				entities->insert(make_pair(elem->Attribute("name"), zone));
			}
		}
	} 
	

	for(TiXmlNode* element = node->FirstChild(); element; element = element->NextSibling())
	{
		if ( node->ToElement() )
		{
			if (!(node->ValueStr().compare("zone")))
				readTopology(sData, element, zone->getEntities(), zone);
			else 
				readTopology(sData, element, entities, parent);
		}
	}
}

void XMLTool::readDeployments(ServerData* sData, TiXmlNode* node)
{
	int id = 0;
	int size = 0;
	int chunkSize = 0;
	Entity* entity = NULL;
	
	string name ="";
	
	
	try
	{
		if ( node->ToElement() )
		{
			TiXmlElement* parentElem = (node->Parent())->ToElement();
			TiXmlElement* elem = node->ToElement();
			if (!(node->ValueStr().compare("file")))
			{
				elem->QueryIntAttribute("id", &id);
				elem->QueryIntAttribute("size", &size);
				elem->QueryIntAttribute("chunkSize", &chunkSize);
			
				name = elem->Attribute("path");
				sData->addFile(id,elem->Attribute("path"), size, chunkSize);
				
			}
			if (!(node->ValueStr().compare("zone")) || !(node->ValueStr().compare("host")))
			{
				entity = sData->public_getEntity(elem->Attribute("ref"));
				if (entity != NULL)
				{
					parentElem->QueryIntAttribute("id", &id);
					sData->fillDeployFiles(entity, id);
				}
			}	
		} 
	

		for(TiXmlNode* element = node->FirstChild(); element; element = element->NextSibling())
		{
			if ( node->ToElement() )
				readDeployments(sData, element);
		}
	} catch (OpenFileException)
	{
		cout << "Fail load : " << name << endl;
	}
}

void XMLTool::writeFileIntoDeployments(int id, string path, int size, int chunkSize)
{
	TiXmlElement *f = DOMDeployments.FirstChildElement();
	TiXmlElement newFile ("file");
	newFile.SetAttribute("id", id);
	newFile.SetAttribute("path", path);
	newFile.SetAttribute("size", size);
	newFile.SetAttribute("chunkSize", chunkSize);
	f->InsertEndChild(newFile);
	DOMDeployments.SaveFile(deploymentsFile);

}

void XMLTool::writeEntityIntoFile(int fileId, Entity* entity)
{
	bool find = false;
	int id;
	TiXmlHandle hdl(&DOMDeployments);
	TiXmlElement *file = hdl.FirstChildElement().FirstChildElement().Element();
	
	if (entity != NULL)
	{
		while(file && !find)
		{
			file->QueryIntAttribute("id", &id);
			if(id == fileId)
			{
				find = true;
				if (entity->getIP() != NULL)
				{
					TiXmlElement newEntity ("host");
					newEntity.SetAttribute("ref", entity->getName());				
					file->InsertEndChild(newEntity);
				} else
				{
					TiXmlElement newEntity ("zone");
					newEntity.SetAttribute("ref", entity->getName());				
					file->InsertEndChild(newEntity);
				}
			}
			file = file->NextSiblingElement();
		}
	
		if (!find)
			cerr << "user inexistant" << endl;
		DOMDeployments.SaveFile(deploymentsFile);
	} 

}
	
void XMLTool::public_displayTopology() 
{ 
	displayTopology(DOMTopology.RootElement()); 
}


