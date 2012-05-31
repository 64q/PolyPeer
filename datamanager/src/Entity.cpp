#include <iostream>

#include <Entity.hpp>

using namespace std;

Entity::Entity(const std::string& name, Entity* parent, int networkCapacity) :
	name(name), parent(parent), networkCapacity(networkCapacity)
{
	gettimeofday(&timerSpeed, NULL);
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

void Entity::setTimerSpeed(int seconds, int milliseconds)
{
	gettimeofday(&timerSpeed, NULL);
	timerSpeed.tv_sec += seconds;
	// On multiplie par 1000 pour avoir des u-seconds
	timerSpeed.tv_usec += (milliseconds*1000);	
}

bool Entity::getTimerSpeed()
{
	timeval currentTime;
	gettimeofday(&currentTime, NULL);
	
	double saveTimer = timerSpeed.tv_sec + (timerSpeed.tv_usec/1000000.0);
	double currentTimer = currentTime.tv_sec + (currentTime.tv_usec/1000000.0);
	
	return (saveTimer <= currentTimer);
}

EntityType Entity::getType() 
{ 
	return type; 
}
