#include <iostream>

#include <Entity.hpp>
#include <Host.hpp>


using namespace std;

Host::Host(const std::string& name, Entity* parent, int networkCapacity, const std::string& ip):
	Entity(name, parent, networkCapacity), ip(ip)
{
	hostState = OFFLINE;
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

State Host::getHostState()
{
	return hostState;
}

void Host::setHostState(State s)
{
	hostState = s;
}
