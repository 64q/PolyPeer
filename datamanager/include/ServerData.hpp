#ifndef __H__SERVERDATA__
#define __H__SERVERDATA__

#include <string>
#include <iostream>
#include <map>
#include <list>


#include <Entity.hpp>
#include <Zone.hpp>
#include <Host.hpp>
#include <File.hpp>
#include <XMLTool.hpp>
#include <FileManager.hpp>
#include <ConnectionManager.hpp>
#include <Packet.hpp>

/**
 * Classe contenant les différentes structures de stockage des données ainsi que
 * les accesseurs associés
 */
 
class XMLTool;

class ServerData
{

public :

	/**
	 * Constructeur d'un ServerData
	 */
	ServerData();
	
	/**
	* Destructeur
	*/
	~ServerData();

	/**
	* Retourne un pointeur vers xmlTool
	*/
	XMLTool* getXMLTool();
	
	/**
	* Retourne un pointeur vers la structure contenant la topologie du réseau
	*/
	map<string, Entity*>* getEntities();
	
	/**
	* Retourne un pointeur vers la structure contenant les différents fichiers
	* à deployer
	*/
	vector<File*>* getDeployFiles();
	
	/**
	* Ajout d'un fichier de déploiement dans DeployFiles
	* @param f
	*	File à ajouter
	*/
	FileManager* addFile(File* f);
	
	/**
	* Ajout d'un fichier de déploiement dans DeployFiles ainsi que dans le fichier XML
	* @param f
	*	File à ajouter
	*/
	void addFileToAll(File* f);
	
	/**
	* Renvoi l'id courante qui sert lors de la création d'un nouveau déploiement
	*/
	int getCurrentId();
	
	/**
	* Cherche un fichier de déploiement dans DeployFiles en fonction de son id et
	* retourne un pointeur vers cet objet
	* @param id
	*	identifiant du fichier recherché
	*/
	File* getFile(int id);
	
	/**
	* Création et ajout d'un Host dans hosts et retourne un pointeur vers ce nouvel objet
	* @param name
	*	nom de l'Host à creer
	* @param address
	*	adress de l'Host à creer
	*/	
	Entity* addHost(string name, Entity* parent,int networkCapacity, string address);
	
	/**
	* Récupération de la structure hosts stockant les Host du réseau
	*/
	vector<Entity*>* getHosts();
	
	/**
	* Recherche et retour d'un pointeur vers un Host en fonction de son nom
	* @param name
	*	nom de l'Host à rechercher
	*/
	Entity* getHostByName(string name);
	
	/**
	* Recherche et retour d'un pointeur vers un Host en fonction de son adresse
	* @param address
	*	address de l'Host à rechercher
	*/
	Entity* getHostByAddress(string address);
	
	/**
	* Recherche et retour d'un pointeur vers le fileManager du fichier
	* qui a l'id spécifié
	* @param fileID
	*	id du fichier 
	*/
	FileManager* getFileManager(int fileID);
	
	/**
	* Retourne le connectionManager
	*/		
	ConnectionManager* getConnectionManager();
	
	/**
	* Retourne l'adresse du serveur
	*/		
	string getAddressServ();
	
	/**
	* Met à jour le numéro de Chunk du fichier passé en paramètre déjà 
	* récupéré par l'Host qui est passé en paramètre
	* @param addressHost
	*	host à mettre à jour
	* @param fileID
	*	identifiant du fichier correspondant à la mise à jour
	* @param nbChunk
	*	nouvelle valeur du Chunk courant
	*/
	void updateHost(string addressHost, int fileID, int nbChunk);
	
	/**
	* Met à jour l'état de l'Host passé en paramètre, ainsi que le fichier 
	* d'identifiant fileID
	* @param addressHost
	*	host à mettre à jour
	* @param fileID
	*	identifiant du fichier correspondant à la mise à jour
	* @param s
	*	nouvel état
	*/
	void updateHost(string addressHost, int fileID, State s);
	
	/**
	* Met à jour l'état de l'Host passé en paramètre
	* Spécifique à l'action envoie d'opération
	* @param addressHost
	*	host à mettre à jour
	* @param s
	*	nouvel état -> WAIT
	*/
	void updateHost(string addressHost, State s);
	
	/**
	* Affichage de la structure contenant la topologie du réseau
	*/	
	void public_displayEntities();
	
	/**
	* Recherche et retourne un pointeur vers une entité en fonction de son nom
	* @param entityName
	*	nom de l'entitié recherchée
	*/
	Entity* public_getEntity(string entityName);
	
	/**
	* Récupère et stocke dans une liste les adresses contenues dans une entité
	* en fonction de son nom
	* @param entityName
	* 	nom de l'entité dont on cherche les adresses
	* @param list
	*	liste à remplir
	*/
	void public_fillAddressList(string entityName, list<string> &list);
	


protected :
	/**
	 * Map représentant la topologie et contenant des pointeurs vers les différentes
	 * entités du réseau
	 */
	map<string, Entity*> entities;
	
	/**
	 * Vecteur contenant des pointeurs vers les structures représentant les
	 * fichiers à déployer
	 */		
	vector<File*> deployFiles;
	
	/**
	 * Vecteur contenant des pointeurs vers les Host du réseau
	 */	
	vector<Entity*> hosts;
	
	/**
	 * Pointeur vers un connectionManager
	 */	
	ConnectionManager* cM;
	
	/**
	 * Adresse du serveur principal
	 */
	string addressServ;
	
	/**
	* Contient la DOM des fichiers de déploiement et de topologie
	*/
	XMLTool* xmlTool;

private :

	void deleteMap(map<string, Entity*>* entities, vector<string> &alreadyDelete);
	void deleteDeployFiles();
	void deleteHosts();
	void displayEntities(map<string, Entity*>* entities, int level = 0);
	Entity* getEntity(map<string, Entity*>* entities, string entityName);
	void fillAddressList(Entity* entity, list<string> &list);

};

#endif
