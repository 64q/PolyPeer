#ifndef SHAREDEPLOYMENT_H
#define SHAREDEPLOYMENT_H

/*
 * Classe ShareDeployment
 *
 * Cette classe est une implémentation d'un algorithme de déploiement
 * Elle hérite de la classe DeploymentAlgorithm qui sert d'interface
 *
 *
 * Cet algo de déploiement se base sur les zones.
 * 	-> Choix d'un client maitre sur chaque zone qui recoit tout le fichier
 *	-> déploiement en arbre à partir du maitre sur la zone (en parallele de l'action précédente)
 * 	-> Si il y a plusieurs déploiements, ils se font en même temps
 * 	-> Il n'y a pas de gestion de déploiement prioritaire
 *
 *
 * par Olivier
 */

// Inherite Class
#include <DeploymentAlgorithm.hpp>

// STL
#include <vector>

// forward declaration
class PolypeerServer;
class ServerData;
class Entity;
class File;


class ShareDeployment : public DeploymentAlgorithm
{
public:
	ShareDeployment(PolypeerServer* pps, ServerData* sd);
	~ShareDeployment();
	
	/**
	 * Exécute une étape de l'algorithme
	 * Si il n'y a rien à faire, il ne se passe rien
	 */
	void nextStep();
	
private:
	/**
	 * Instance du serveur principale
	 */ 
	PolypeerServer* ppServer;
	
	/**
	 * Instance de la structure principale
	 */
	ServerData* sData;
	
	/**
	 * Etat initial
	 * cas particulier du lancement où il faut se mettre à jour
	 */
	bool firstLaunch;
	
	/**
	 * Scan du réseau
	 */
	void networkScan(std::vector<std::vector<Entity*>* >* entities, File* f);
	
	/**
	 * Break des download failed
	 */
	void resetBreakHost(std::vector<std::vector<Entity*>* >* entities);
	
	void sendOnMaster(Entity* entity, File* file);
	
	/**
	 * vérifie que le déploiement est bien fini
	 */
	bool isEnd(std::vector<std::vector<Entity*>* >* entities, int idFile);
	
	/**
	 * sélectionner le maitre d'une zone
	 */
	Entity* selectZoneMaster(std::vector<Entity*>* zone, int idFile);
	
	/**
	 * Récupérer l'host le moins avancé de la zone
	 */
	Entity* getMinZoneDeployment(std::vector<Entity*>* zone, int idFile);

	/**
	 * Récupérer l'host le plus avancé de la zone
	 */
	Entity* getSeedZoneDeployment(std::vector<Entity*>* zone, int idFile, long chunkId);
		
	 
};


#endif //SHAREDEPLOYMENT_H

