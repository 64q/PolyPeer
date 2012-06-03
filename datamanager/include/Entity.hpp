#ifndef __H_ENTITY__
#define __H_ENTITY__

#include <map>
#include <vector>
#include <string>
#include <ctime>
#include <sys/time.h>

#include <DeploymentState.hpp>
#include <State.hpp>
#include <File.hpp>

class DeploymentState;
class File;

/**
 * Une entité peut être une zone ou un client
 */
 
enum EntityType { HOST = 0, ZONE };

class Entity
{
public:

	/**
	 * Contructeur d'une entité
	 * @param name
	 * 	nom de l'entité
	 * @param parent
	 *	 pointeur vers l'entité contenant l'entité à créer
	 * @param networkCapacity
	 *	 capacité réseau entre l'entité et son père
	 */
	Entity(const std::string& name, Entity* parent, int networkCapacity);
	
	/**
	 * Destructeur de l'entité
	 */
	~Entity();
	
	/**
	 * Retourne le nom de l'entité
	 */
	std::string getName();
	
	/**
	 * Retourne un pointeur vers le parent de l'entité
	 */
	Entity* getParent();
	
	/**
	 * Retourne le débit courant qui traverse l'entité
	 */
	int getCurrentBroadbandSpeed();
	
	/**
	 * Permet de mettre à jour le débit courant qui traverse une entité, si bbs est suppérieur à la
	 * capacité alors la fonction retourne false
	 * @param bbs
	 *	 nouveau débit de l'entité
	 */
	bool setCurrentBroadbandSpeed(int bbs);
	
	/**
	 * Retourne la capacité réseau d'une entité
	 */
	int getNetworkCapacity();
	
	/**
	 * Calcul automatiquement le nouveau temps avec la taille du paquet
	 * utilise setTimerSpeed
	 */
	void calculNewTimerSpeed(unsigned int packetSizeInOctet);
	
	/**
	 * Permet de mettre à jour timerSpeed avec une nouvelle date butoire
	 * @param seconds 
	 *	 nombre de secondes estimée avant la fin du téléchargement
	 * @param milliseconds
	 *	 nombre de microseconds estimée avant la fin du téléchargement
	 */
	void setTimerSpeed(int seconds, int microseconds);
	
	/**
	 * Vérifie si la date actuelle est suppérieure à celle stockée dans le timerSpeed
	 */
	bool getTimerSpeed();
	
	/**
	 * Retourne le type de l'entité
	 */
	EntityType getType();

	/**
	 * Retourne un pointeur vers la map d'entités d'une Zone
	 */
	virtual std::map<std::string, Entity*>* getEntities() = 0;
	
	/**
	 * Retourne un pointeur vers la liste des déploiements d'un Host
	 */
	virtual std::vector<DeploymentState>* getDeploys() = 0;
	
	/**
	 * Retourne l'adresse ip d'un Host
	 */
	virtual std::string getIP() = 0;
	
	/**
	 * Retourne l'adresse mac d'un Host
	 */
	virtual std::string getMac() = 0;
	
	/**
	 * Retourne le masque de sous réseau d'un Host
	 */
	virtual std::string getMask() = 0;
	
	/**
	 * permet d'ajouter un nouveau déploiement dans la structure d'un Host
	 * @param cid
	 *	 numéro du chunk courant
	 * @param f
	 *	 pointeur vers le déploiement pour pouvoir en récupérer les informations
	 *	@param s
	 *	 nouvel état de l'Host
	 */
	virtual void addDeploymentState(const int cid, File* f, HostDeployState s) = 0;
	
	/**
	 * Retourne un pointeur vers le DeploymentState d'id passé en paramètre
	 * @param idFile
	 *	 id du fichier à déployer recherché
	 */
	virtual DeploymentState* getDeploymentState(int idFile) = 0;
	
	/**
	 * Retourne l'etat d'un Host
	 */
	virtual HostState getHostState() = 0;
	
	/**
	 * Met à jour l'etat d'un Host
	 * @param hs
	 *	 nouvel état de l'Host
	 */
	virtual void setHostState(HostState hs) = 0;
	
	/**
	 * Met à la date actuelle le timerState de l'Host
	 */
	virtual void setTimerState() = 0;
	
	/**
	 * Retourne la différence entre la date actuelle et la dernière fois que l'Host à été contacté
	 */
	virtual double getTimerState() = 0;

	
protected:
	/**
	 * Nom de l'entité
	 */
	std::string name;
	
	/**
	 * Entité parente de l'entité
	 */
	Entity* parent;
	
	/**
	 * Débit courant qui traverse l'entité
	 */
	int currentBroadbandSpeed;
	
	/**
	 * Contient l'estimation de la date de fin du téléchargement passant par l'entité
	 */ 
	timeval timerSpeed;
	
	/**
	 * Capacité réseau de l'entité
	 */
	int networkCapacity;
	
	/**
	 * Type de l'entité Host ou Zone
	 */
	EntityType type;
};

#endif
