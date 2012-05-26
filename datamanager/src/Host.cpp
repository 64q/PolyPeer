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

DeploymentState* Host::getDeploymentState(int idFile)
{
	unsigned int i=0;
	DeploymentState* ds = NULL;
	while(i < deploys.size() && ds == NULL)
	{
	
		if (deploys[i].getRefFile()->getFileManager()->getIdFile() == idFile)
			ds = &(deploys[i]);
			
		i++;
	}
	return ds;
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
