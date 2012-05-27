#ifndef __H_DEPLOYMENTSTATE__
#define __H_DEPLOYMENTSTATE__

#include <File.hpp>
#include <State.hpp>

class File;

class DeploymentState
{
	
public:
	
	/**
	* Constructeur
	*	@currentIdChunk
	*		id du chunk courant
	*	@file
	*		pointeur vers le fichier de déploiement correspondant
	*	@HostDeployState
	*		Etat courant du déploiement pour l'Host donné
	*/
	DeploymentState(const int currentIdChunk, File* file, HostDeployState s);
	
	/**
	* Retourne l'id du chunk courrant
	*/
	int getCurrentIdChunk() { return currentIdChunk; }
	
	/**
	* Retourne l'id du déploiement
	*/
	int getId();
	
	/**
	* Retourne un pointeur vers le déploiement
	*/
	File* getRefFile() { return refFile; }
	
	/**
	* Retourne l'etat courrant
	*/
	HostDeployState getCurrentState() { return currentState; }
	
	/**
	* Change l'id du chunk courrant
	*	@id 
	*		nouvelle id du chunk courrant
	*/
	void setCurrentIdChunk(int id) { currentIdChunk = id; }
	
	/**
	* Change l'etat du déploiement 
	*	@id 
	*		nouvel etat du déploiement
	*/
	void setCurrentState(HostDeployState s);

private:

	/**
	* Id du chunk auquel l'host est rendu
	*/
	int currentIdChunk;
	
	/**
	* Référence qui contient les informations du déploiement
	*/
	File* refFile;
	
	/**
	* Etat courant du déploiement pour l'Host donné
	*/
	HostDeployState currentState;
	
};


#endif
