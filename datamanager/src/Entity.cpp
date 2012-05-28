#include <iostream>

#include <Entity.hpp>

using namespace std;

Entity::Entity(const std::string& name, Entity* parent, int networkCapacity) :
	name(name), parent(parent), networkCapacity(networkCapacity)
{
	setTimerSpeed();
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

int Entity::getCurrentBroadbandSpeed()
{
	return currentBroadbandSpeed;
}

bool Entity::setCurrentBroadbandSpeed(int bbs)
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

void Entity::setTimerSpeed()
{
	time_t currentTime;
	time ( &currentTime );
	timerSpeed = currentTime;	
}

double Entity::getTimerSpeed()
{
	time_t currentTime;
	time ( &currentTime );
	return difftime (currentTime,timerSpeed);
}

EntityType Entity::getType() 
{ 
	return type; 
}
