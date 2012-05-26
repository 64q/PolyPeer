#ifndef __H__CLIENTDATA__
#define __H__CLIENTDATA__

#include <string>
#include <iostream>

#include <FileManager.hpp>
#include <ConnectionManager.hpp>
#include <Packet.hpp>

class ClientData 
{

public :
	
	/**
	 * Constructeur d'un ClientData
	 */
	ClientData();
	
	/**
	* Destructeur
	*/
	~ClientData();

	/**
	* Retourne un pointeur vers deploys
	*/	
	vector<FileManager*>* getDeploys();
	
	/**
	* Retourne le connectionManager
	*/		
	ConnectionManager* getConnectionManager();
	
	/**
	* Retourne l'adresse du serveur
	*/		
	string getAddressServ();
	
	/**
	* Ajoute le fileManager passé en paremètre à deploys
	*/	
	void addFileManager(FileManager* fm);
	
	/**
	* Récupère le fileManager d'id passé en paramètre
	*/	
	FileManager* getFileManager(int id);
	
protected :
	/**
	 * Vecteur contenant des pointeurs vers les FileManager des déploiements en cours
	 */		
	vector<FileManager*> deploys;
	
	/**
	 * Pointeur vers un connectionManager
	 */	
	ConnectionManager* connectionManager;
	
	/**
	 * Adresse du serveur principal
	 */
	string addressServ;
};

#endif
