#ifndef __H_HOST__
#define __H_HOST__

#include <vector>
#include <map>
#include <string>

#include <Entity.hpp>

class Host : public Entity
{	
public:

	Host(const std::string& name, const std::string& ip);
	~Host();
	void addDeploymentState(const int, File* file, State);
	std::vector<DeploymentState>* getDeploys();
	std::string* getIP();
	State getHostState();
	void setHostState(State);
	std::map<std::string, Entity*>* getEntities();

private:
	State hostState;
	std::string ip;
	std::vector<DeploymentState> deploys;

};

#endif
