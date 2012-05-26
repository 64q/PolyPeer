#ifndef __H_ENTITY__
#define __H_ENTITY__

/**
 * Une entité sur le réseau
 */
#include <map>
#include <vector>
#include <string>

#include <DeploymentState.hpp>
#include <State.hpp>
#include <File.hpp>

class DeploymentState;
class File;

class Entity
{
public:
	/**
	 * Contructeur d'une entité
	 * @param string name
	 * 	nom de l'entité
	 */
	Entity(const std::string& name, Entity* parent, int networkCapacity);
	std::string getName();
	Entity* getParent();
	double getCurrentBroadbandSpeed();
	void setCurrentBroadbandSpeed(double bbs);
	int getNetworkCapacity();
	~Entity();
	virtual std::map<std::string, Entity*>* getEntities() = 0;
	virtual std::vector<DeploymentState>* getDeploys() = 0;
	virtual std::string* getIP() = 0;
	virtual void addDeploymentState(const int, File*, State) = 0;
	virtual State getHostState() = 0;
	virtual void setHostState(State) = 0;
	
protected:
	/**
	 * Nom de l'entité
	 */
	std::string name;
	Entity* parent;
	double currentBroadbandSpeed; 
	int networkCapacity;
};

#endif
