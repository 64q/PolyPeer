#include <iostream>

#include <Zone.hpp>

using namespace std;

Zone::Zone(const std::string& name) :
	Entity(name)
{

}

Zone::~Zone()
{
}

void Zone::addDeploymentState(const int, File*, State)
{

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

State Zone::getHostState()
{
	return WAIT;
}

void Zone::setHostState(State)
{
}


