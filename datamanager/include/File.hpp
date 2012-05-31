#ifndef __H__FILE__
#define __H__FILE__

#include <set>
#include <iostream>
#include <ctime>

#include <Entity.hpp>
#include <State.hpp>
#include <FileManager.hpp>
#include <State.hpp>

/**
 * Classe contenant les informations d'un fichier à déployer
 */
	
class Entity;

class File
{

public :

	/**
	 * Constructeur qui est utilisé lors de la création du fichier par l'interface web
	 * @param id
	 *	 id du nouveau fichier à déployer
	 * @param serverPath
	 *	 chemin sur le serveur vers le fichier à déployer
	 * @param clientPath
	 *	 chemin de destination du déploiement sur le client
	 */
	File(int id, std::string name, std::string serverPath, std::string clientPath);
	File(int id, std::string name, std::string serverPath, std::string clientPath, int chunkSize);
	
	/**
	 * Constructeur qui est utilisé lors de la création du fichier par la lecture du fichier XML
	 * @param id
	 *	 id du nouveau fichier à déployer
	 * @param serverPath
	 *	 chemin sur le serveur vers le fichier à déployer
	 * @param clientPath
	 *	 chemin de destination du déploiement sur le client
	 * @param chunkSize
	 *	 taille de chaque segment de fichier que nous envoyons
	 * @param fs
	 *	 etat du déploiement
	 * @param dateFile
	 *	 date à laquelle le déploiement à été créé 
	 */
	File(int id, std::string name, std::string serverPath, std::string clientPath, int chunkSize, FileState fs, long dateFile);
	
	/**
	 * Destructeur de la classe
	 */
	~File();
	
	/**
	 * Retourne le nom du déploiement
	 */
	std::string getName() { return name; }
	
	/**
	 * Retourne un pointeur vers le fileManager correspondant au fichier à déployer
	 */
	FileManager* getFileManager() { return fileM; }
	
	/**
	 * Retourne l'état courant 
	 */
	FileState getFileState() { return fState; }
	
	/**
	 * Retourne le chemin chez le client vers lequel le fichier va être déployer
	 */
	std::string getClientPath() { return clientPath; }
	
	/**
	 * Retourne la date à laquelle le déploiement a été créé
	 */
	long getDate() { return date; }
	
	/**
	 * Retourne un pointeur vers la structure contenant l'ensemble des Entités sur lesquelles 
	 * déployer le fichier
	 */
	std::vector<Entity*>* getDeploysOn() { return &deploysOn; }
	
	/**
	 * Permet de modifier l'état courant du déploiement 
	 * @param fs
	 *	 nouvel état du déploiement
	 */
	void setFileState(FileState fs);
	
	/**
	 * Fonction qui permet de renvoyer les differents Hosts sur lesquels déployer le nouveau
	 * fichier, ceux-ci sont classé par zone dans des vecteurs spécifiques
	 */
	std::vector<std::vector<Entity*>* >* getSortedHosts();
	
	/**
	 * Fonction de désallocation de la structure retournée par de getSortedHosts
	 * @param v
	 *	 vecteur de vecteurs à désallouer
	 */
	static void deleteSortedHost(std::vector<std::vector<Entity*>* >* v);
	
	/**
	 * Fonction qui permet d'ajouter une nouvelle entité à deploysOn, si c'est une Zone, seul les 
	 * Hosts qu'elle contient sont ajoutés
	 * @param entity
	 *	 nouvelle entité sur laquelle il faut déployer le fichier
	 */
	void addEntity(Entity* entity);
	
	/**
	 * Fonction qui retourne l'entité de nom passé en paramètre
	 * @param name
	 *	 nom de l'entité recherchée
	 */
	Entity* getEntity(std::string name);
	
protected :
	
	/**
	 * Data à laquelle le déploiement a été créé
	 */
	time_t date;
	
	/**
	 * Nom du fichier à déployer
	 */
	std::string name;
	
	/**
	 * Chemin chez le client vers lequel le fichier va être déployer
	 */
	std::string clientPath;
	
	/**
	 * Pointeur vers la structure de fileManager
	 */
	FileManager* fileM;
	
	/**
	 * Etat courant du fichier à déployer
	 */
	FileState fState;
	
	/**
	 * Vecteur qui contient l'ensemble des clients sur lesquels déployer le fichier
	 */
	std::vector<Entity*> deploysOn;
	
};

#endif


