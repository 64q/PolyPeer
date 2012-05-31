#ifndef __H_ZONE__
#define __H_ZONE__

#include <map>

#include <Entity.hpp>

class Zone : public Entity
{
public:
	/**
	 * Constructeur d'une zone
	 * @param string name
	 * 	nom de la zone
	 */
	Zone(const std::string& name, Entity* parent, int networkCapacity);
	~Zone();
	void addDeploymentState(const int, File*, HostDeployState hds);
	DeploymentState* getDeploymentState(int idFile);
	std::map<std::string, Entity*>* getEntities();
	std::vector<DeploymentState>* getDeploys();
	std::string getIP();
	std::string getMac();
	HostState getHostState();
	void setHostState(HostState);
	void setTimerState();
	double getTimerState();
	
private:
	std::map<std::string, Entity*> entities;

	
};

#endif
