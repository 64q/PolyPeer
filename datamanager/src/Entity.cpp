#include <iostream>

#include <Entity.hpp>

using namespace std;

Entity::Entity(const std::string& name, Entity* parent, int networkCapacity) :
	name(name), parent(parent), networkCapacity(networkCapacity)
{
	currentBroadbandSpeed = 0;
}

Entity::~Entity()
{
}

std::string Entity::getName()
{
	return name;
}

Entity* Entity::getParent()
{
	return parent;
}

double Entity::getCurrentBroadbandSpeed()
{
	return currentBroadbandSpeed;
}

bool Entity::setCurrentBroadbandSpeed(double bbs)
{
	if ((bbs <= networkCapacity) && (bbs >= 0))
	{
		currentBroadbandSpeed = bbs;
		return true;
	} else 
		return false;
}
	
int Entity::getNetworkCapacity()
{
	return networkCapacity;
}
