#include <iostream>

#include <Entity.hpp>
#include <Host.hpp>


using namespace std;

Host::Host(const std::string& name, Entity* parent, int networkCapacity, const std::string& ip):
	Entity(name, parent, networkCapacity), 
	hostState(OFFLINE),
	ip(ip)
{
	setTimerState();
	this->type = HOST;
}

Host::~Host()
{
}

void Host::addDeploymentState(const int cid, File* file, HostDeployState hds)
{
	deploys.push_back(DeploymentState(cid, file, hds));
}

DeploymentState* Host::getDeploymentState(int idFile)
{
	unsigned int i=0;
	DeploymentState* ds = NULL;
	while(i < deploys.size() && ds == NULL)
	{
		if (deploys[i].getRefFile()->getFileManager() != NULL)
		{
			if (deploys[i].getRefFile()->getFileManager()->getIdFile() == idFile)
				ds = &(deploys[i]);
		}
			
		i++;
	}
	return ds;
}

std::vector<DeploymentState>* Host::getDeploys()
{
	return &deploys;
}

std::string Host::getIP()
{
	return ip;
}

map<std::string, Entity*>* Host::getEntities()
{
	return NULL;
}

HostState Host::getHostState()
{
	return hostState;
}

void Host::setHostState(HostState s)
{
	hostState = s;
}

void Host::setTimerState()
{
	time_t currentTime;
	time ( &currentTime );
	timerState = currentTime;
}

double Host::getTimerState()
{
	time_t currentTime;
	time ( &currentTime );
	return difftime (currentTime,timerState);
}
