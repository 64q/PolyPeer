#include <iostream>

#include <Zone.hpp>

using namespace std;

Zone::Zone(const std::string& name, Entity* parent, int networkCapacity) :
	Entity(name, parent, networkCapacity)
{
	this->type = ZONE;
}

Zone::~Zone()
{
}

void Zone::addDeploymentState(const int, File*, HostDeployState)
{

}

DeploymentState* Zone::getDeploymentState(int idFile)
{
	return NULL;
}


std::map<std::string, Entity*>* Zone::getEntities()
{
	return &entities;
}

std::vector<DeploymentState>* Zone::getDeploys()
{
	return NULL;
}

std::string* Zone::getIP()
{
	return NULL;
}

HostState Zone::getHostState()
{
	return OFFLINE;
}

void Zone::setHostState(HostState)
{
}


