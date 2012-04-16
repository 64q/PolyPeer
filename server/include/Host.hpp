#ifndef __H_HOST__
#define __H_HOST__

#include <vector>

#include <Entity.hpp>
#include <DeploymentState.hpp>

class Host : public Entity
{
private:
	std::string ip;
	
	std::vector<DeploymentState> deploys;
	
public:
	Host(const std::string& name, const std::string& ip);
	void addDeploymentState(const int, const int, const std::string);
};

#endif
