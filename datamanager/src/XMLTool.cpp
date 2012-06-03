#include <XMLTool.hpp>
#include <OpenFileException.hpp>
#include <CreateFileException.hpp>


using namespace std;

XMLTool::XMLTool(ServerData* sData)
{
	topologyFile = string("topology.xml");
	deploymentsFile = string("deployments.xml");
	
	//Chargement en mémoire des deux fichiers
	TiXmlDocument DOMT(topologyFile);
	TiXmlDocument DOMD(deploymentsFile);
	DOMTopology = DOMT;
	DOMDeployments = DOMD;
	
	//Vérification qu'il n'y a pas eut d'erreur lors du chargement
	if(!DOMTopology.LoadFile())
		cout << "Erreur lors du chargement du fichier de topologie" << topologyFile << endl;
	else 
	{
		//Création de la topologie dans la map
		readTopology(sData, DOMTopology.RootElement(), sData->getEntities(), NULL);
	}
	
	if(!DOMDeployments.LoadFile())
	{
		cout << "Erreur lors du chargement du fichier : " << deploymentsFile << endl;
	} else 
	{
		//Ajout des états de déploiement dans la map
		readDeployments(sData, DOMDeployments.RootElement());
	}

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
	
	try
	{
		if ( node->ToElement() )
		{
			TiXmlElement* elem = node->ToElement();
			
			//Si c'est une balise Host
			if (!(node->ValueStr().compare("host")))
			{
				//Si c'est une balise qui contient une référence vers un Host
				if (elem->Attribute("ref") != NULL )
				{
					// Nous cherchons la référence de l'Host dans la structure partiellement remplie
					entity = sData->getHostByName(elem->Attribute("ref"));
					if (entity != NULL)
						entities->insert(make_pair(elem->Attribute("ref"), entity));
					else 
						cout << "reference inexistante" << endl;
				}else
				{
					//Dans le cas contraire nous créons l'Host à partir des informations contenues dans la balise et l'ajoutons à la structure
					elem->QueryIntAttribute("networkCapacity", &capacity);
					entity = sData->addHost(elem->Attribute("name"), parent, capacity, elem->Attribute("address"), elem->Attribute("mac"));
					entities->insert(make_pair(elem->Attribute("name"), entity));
				}
			}
			
			//Si c'est une balise Zone
			if (!(node->ValueStr().compare("zone")))
			{
				//Cas de la balise référence et de création similaire à Host
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
	
		//Parcours des balises du même niveau, si l'une d'elle contient des filles : appel récurssif de la fonction 
		for(TiXmlNode* element = node->FirstChild(); element; element = element->NextSibling())
		{
			if ( node->ToElement() )
			{
				//Si c'est une balise zone alors nous changeons la map à remplir et le parent courant
				if (!(node->ValueStr().compare("zone")))
					readTopology(sData, element, zone->getEntities(), zone);
				else 
					readTopology(sData, element, entities, parent);
			}
		}
		
	} catch(...)
	{
		if ( node->ToElement() )
		{
			TiXmlElement* elem = node->ToElement();
			cout << "Problème dans la construction du fichier de topologie, il manque peut être des attributs dans une balise " << node->ValueStr();
			if (!(node->ValueStr().compare("host")) || !(node->ValueStr().compare("host")))
			{
				if (elem->Attribute("name") != NULL)
					cout << ", de nom : " << elem->Attribute("name") << "." << endl;
				else 
					cout << ", son nom est introuvable." << endl;
			}
		}		
	}
}

void XMLTool::readDeployments(ServerData* sData, TiXmlNode* node)
{
	int id = 0;
	int chunkSize = 0;
	int date = 0;
	Entity* entity = NULL;

	string name ="";

	try
	{
		if ( node->ToElement() )
		{
			//Récupération de la balise parente
			TiXmlElement* parentElem = (node->Parent())->ToElement();
			TiXmlElement* elem = node->ToElement();
			
			//Si c'est une balise File
			if (!(node->ValueStr().compare("file")))
			{
				//Récupération de l'etat, si il est à FINISH nous ne chargeons pas le déploiement en mémoire
				FileState fs =  getFileStateString(elem->Attribute("state"));
				if (fs != FINISH)
				{
					//Si il y a la moindre exception sur le déploiement (manque d'attribut(s), chemin incorrect, ou fichier deja en déploiement alors le File n'est pas créé et ajouté
					elem->QueryIntAttribute("id", &id);
					elem->QueryIntAttribute("chunkSize", &chunkSize);
					elem->QueryIntAttribute("date", &date);
					File *f = new File(id, elem->Attribute("name"), elem->Attribute("serverPath"), elem->Attribute("clientPath"), chunkSize, fs, (long)date);
					sData->addFile(f);
				}
			}
			if (!(node->ValueStr().compare("zone")) || !(node->ValueStr().compare("host")))
			{
				//Récupération de la référence vers l'entité contenue dans la balise File
				entity = sData->public_getEntity(elem->Attribute("ref"));
				if (entity != NULL)
				{
					parentElem->QueryIntAttribute("id", &id);
					File* f = sData->getFile(id);
					if (f != NULL)
						f->addEntity(entity);
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
		cout << "Problème dans le fichier de déploiement : " << name << endl;
	} catch (CreateFileException)
	{
		cout << "Problème lors du chargement d'un déploiment." << endl;
	} catch (...)
	{
		 if ( node->ToElement() )
		{
			TiXmlElement* elem = node->ToElement();
			cout << "Problème dans la construction du fichier de déploiement, il manque peut être des attributs dans une balise " << node->ValueStr();
			if (!(node->ValueStr().compare("file")))
			{
				if (elem->Attribute("id") != NULL)
					cout << ", d'id : " << elem->Attribute("id") << "." << endl;
				else 
					cout << ", son id est introuvable." << endl;
			}
		}		
	}
}

void XMLTool::writeFileIntoDeployments(File* file)
{

	if (!DOMDeployments.LoadFile())
	{
		TiXmlDocument tmp;
		TiXmlElement deployments ("deployments");
		tmp.InsertEndChild(deployments);
		DOMDeployments = tmp;
	}
	
	//Positionnement sur au niveau des balises File
	TiXmlElement *f = DOMDeployments.FirstChildElement();
	TiXmlElement newFile ("file");
	
	if (file->getFileManager() != NULL)
	{
		newFile.SetAttribute("id", (file->getFileManager())->getIdFile());
		newFile.SetAttribute("name", file->getName());
		newFile.SetAttribute("serverPath", (file->getFileManager())->getFilePath());
		newFile.SetAttribute("clientPath", file->getClientPath());
		newFile.SetAttribute("chunkSize", (file->getFileManager())->getChunkSize());
		newFile.SetAttribute("state", getStringFileState(file->getFileState()));
		newFile.SetAttribute("date", file->getDate());
	}
	
	f->InsertEndChild(newFile);
	DOMDeployments.SaveFile(deploymentsFile);

}

void XMLTool::writeEntityIntoFile(int fileId, Entity* entity)
{

	if (!DOMDeployments.LoadFile())
	{
		bool find = false;
		int id;
		TiXmlHandle hdl(&DOMDeployments);
	
		TiXmlElement *file = hdl.FirstChildElement().FirstChildElement().Element();

		if (entity != NULL)
		{
			//Parcours pour trouver si le File dans lequel ajouter les entité 
			while(file && !find)
			{
				file->QueryIntAttribute("id", &id);
				if(id == fileId)
				{
					find = true;
					if (entity->getType() == HOST)
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
				// Nous passons à la balise File suivante
				file = file->NextSiblingElement();
			}

			DOMDeployments.SaveFile(deploymentsFile);
		}
	}

}
	
void XMLTool::removeDeployment(int fileId)
{

	if (DOMDeployments.LoadFile())
	{
		bool find = false;
		int id;
		TiXmlHandle hdl(&DOMDeployments);
		TiXmlElement *file = hdl.FirstChildElement().FirstChildElement().Element();

		while(file && !find)
		{
			file->QueryIntAttribute("id", &id);
			if(id == fileId)
			{
				find = true;
			} else 
			{
				file = file->NextSiblingElement();
			}
		}

		if (find)
		{
			TiXmlElement *f = DOMDeployments.FirstChildElement();
			f->RemoveChild(file);
			DOMDeployments.SaveFile(deploymentsFile);
		}
	}
}

int XMLTool::getCurrentId()
{
	int id;
	int currentId=0;
	TiXmlHandle hdl(&DOMDeployments);
	TiXmlElement *file = hdl.FirstChildElement().FirstChildElement().Element();

	while(file)
	{
		file->QueryIntAttribute("id", &id);
		if (currentId < id)
			currentId = id;
		file = file->NextSiblingElement();
	}
	return currentId;
}

void XMLTool::public_displayTopology() 
{ 
	displayTopology(DOMTopology.RootElement()); 
}



