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

enum EntityType { HOST = 0, ZONE };

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
	bool setCurrentBroadbandSpeed(double bbs);
	int getNetworkCapacity();
	~Entity();
	virtual std::map<std::string, Entity*>* getEntities() = 0;
	virtual std::vector<DeploymentState>* getDeploys() = 0;
	virtual std::string getIP() = 0;
	virtual void addDeploymentState(const int, File*, HostDeployState) = 0;
	virtual DeploymentState* getDeploymentState(int idFile) = 0;
	virtual HostState getHostState() = 0;
	virtual void setHostState(HostState) = 0;
	EntityType getType() { return this->type; }
	
protected:
	/**
	 * Nom de l'entité
	 */
	std::string name;
	Entity* parent;
	double currentBroadbandSpeed; 
	int networkCapacity;
	EntityType type;
};

#endif
