#include <XMLTool.hpp>
#include <ServerData.hpp>

XMLTool* XMLTool::instance = NULL;

XMLTool::XMLTool()
{
	ServerData* sData = ServerData::getInstance();
	
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
	readTopology(DOMTopology.RootElement(), sData->getEntities());
	//Ajout des états de déploiement dans la map
	readDeployments(DOMDeployments.RootElement());
}

XMLTool* XMLTool::getInstance()
{
	if (instance == NULL)
	{
		instance = new XMLTool();
	}
	
	return instance;
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

void XMLTool::readTopology(TiXmlNode* node, map<string, Entity*>* entities)
{
	Zone* zone = NULL;
	Entity* entity = NULL;
	ServerData* sData = ServerData::getInstance();
	
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
				entity = sData->addHost(elem->Attribute("name"), elem->Attribute("address"));
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
	ServerData* sData = ServerData::getInstance();
	
	if ( node->ToElement() )
	{
		TiXmlElement* parentElem = (node->Parent())->ToElement();
		TiXmlElement* elem = node->ToElement();
		if (!(node->ValueStr().compare("file")))
		{
			elem->QueryIntAttribute("id", &id);
			elem->QueryIntAttribute("size", &size);
			elem->QueryIntAttribute("chunkSize", &chunkSize);
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
			readDeployments(element);
	}
}

void XMLTool::public_displayTopology() 
{ 
	displayTopology(DOMTopology.RootElement()); 
}


