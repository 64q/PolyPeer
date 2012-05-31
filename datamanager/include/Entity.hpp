#ifndef __H_ENTITY__
#define __H_ENTITY__

/**
 * Une entité sur le réseau
 */
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
	std::string getName();
	Entity* getParent();
	int getCurrentBroadbandSpeed();
	bool setCurrentBroadbandSpeed(int bbs);
	int getNetworkCapacity();
	void setTimerSpeed(int seconds, int milliseconds);
	bool getTimerSpeed();
	EntityType getType();
	~Entity();
	
	virtual std::map<std::string, Entity*>* getEntities() = 0;
	virtual std::vector<DeploymentState>* getDeploys() = 0;
	virtual std::string getIP() = 0;
	virtual std::string getMac() = 0;
	virtual void addDeploymentState(const int, File*, HostDeployState) = 0;
	virtual DeploymentState* getDeploymentState(int idFile) = 0;
	virtual HostState getHostState() = 0;
	virtual void setHostState(HostState) = 0;
	virtual void setTimerState() = 0;
	virtual double getTimerState() = 0;

	
protected:
	/**
	 * Nom de l'entité
	 */
	std::string name;
	Entity* parent;
	int currentBroadbandSpeed; 
	timeval timerSpeed;
	int networkCapacity;
	EntityType type;
};

#endif
