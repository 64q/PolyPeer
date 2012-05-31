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

/**
 * Classe contenant les informations des fichiers XML ainsi que les méthodes sur ces fichiers.
 */
 
class XMLTool 
{
	
public :


	/**
	 * Constructeur de la classe qui charge en mémoire les fichiers XML et les parcours pour initialiser les 
	 * structures principales de ServerData
	 * @param sData
	 *	 pointeur pour acceder aux structures principales
	 */
	XMLTool(ServerData* sData);
	
	/**
	 * Destructeur de la classe XMLTool
	 */
	~XMLTool();
	
	XMLTool& operator=(XMLTool& reader); 
	
	/**
	 * Fonction qui permet d'afficher la topologie chargée en mémoire
	 */
	void public_displayTopology();
	
	/**
	 * Fonction qui permet d'écrire dans le fichier de déploiements un nouveau déploiement passé en paramètre
	 * mais sans écrire les entités sur lesquelles il y a le déploiement
	 * @param file
	 *	 pointeur vers le déploiement à insérer
	 */
	void writeFileIntoDeployments(File* file);
	
	/**
	 * Fonction qui permet d'écrire dans le fichier de déploiements dans la balise d'id passé en paramètre
	 * l'entité passée en paramètre
	 * @param fileId
	 *	 id du déploiement dans lequel insérer une nouvelle entité
	 * @param entity
	 *	 pointeur vers l'entité à ajouter dans le fichier XML
	 */
	void writeEntityIntoFile(int fileId, Entity* entity);
	
	/**
	 * Fonction qui permet de supprimer du fichier XML le déploiement d'id passé en paramètre
	 * @param id
	 *	 id du déploiement à supprimer
	 */
	void removeDeployment(int id);
	
	/**
	 * Fonction qui permet de récupérer l'id maximum des déploiements dans le fichier XML
	 */
	int getCurrentId();
	
protected :

	/**
	 * Nom du fichier de topologie
	 */
	std::string topologyFile;
	
	/**
	 * Nom du fichier des déploiements
	 */
	std::string deploymentsFile;
	
	/**
	 * DOM du fichier de topologie chargé en mémoire
	 */
	TiXmlDocument DOMTopology;
	
	/**
	 * DOM du fichier des déploiements chargé en mémoire
	 */
	TiXmlDocument DOMDeployments;
	
private :

	void displayTopology(TiXmlNode* node, int level = 0);
	void readTopology(ServerData* sData, TiXmlNode* node, std::map<std::string, Entity*>* entities, Entity* parent);
	void readDeployments(ServerData* sData, TiXmlNode* node);
	
};



#endif
