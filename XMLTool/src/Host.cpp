#include <iostream>

#include "../include/Entity.hpp"
#include "../include/Host.hpp"


using namespace std;

Host::Host(const std::string& name, const std::string& ip):
	Entity(name), ip(ip)
{

}

Host::~Host()
{
}

void Host::addDeploymentState(const int cid, File* file, State s)
{
	deploys.push_back(DeploymentState(cid, file, s));
}

std::vector<DeploymentState>* Host::getDeploys()
{
	return &deploys;
}

std::string* Host::getIP()
{
	return &ip;
}

map<std::string, Entity*>* Host::getEntities()
{
	return NULL;
}
