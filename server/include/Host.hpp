#ifndef __H_HOST__
#define __H_HOST__

#include <vector>

#include <DeploymentState.hpp>

class Host
{
private:
	std::string name;
	std::string ip;
	
	std::vector<DeploymentState> deploys;
	
public:
	Host(std::string name, std::string ip);
	void addDeploymentState(const int, const int, const std::string);
};

#endif
