#ifndef __H_HOST__
#define __H_HOST__

#include <vector>
#include <map>
#include <string>

#include <Entity.hpp>

class Host : public Entity
{	
public:

	Host(const std::string& name, Entity* parent, int networkCapacity, const std::string& ip);
	~Host();
	void addDeploymentState(const int cid, File* file, HostDeployState hds);
	DeploymentState* getDeploymentState(int idFile);
	std::vector<DeploymentState>* getDeploys();
	std::string getIP();
	HostState getHostState();
	void setHostState(HostState);
	std::map<std::string, Entity*>* getEntities();

private:
	HostState hostState;
	std::string ip;
	std::vector<DeploymentState> deploys;

};

#endif
