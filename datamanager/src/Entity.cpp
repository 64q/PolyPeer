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
	// remise à jour du time
	gettimeofday(&timerSpeed, NULL);
	
	// récupération du time en paramètre
	timeval givenTime;
	givenTime.tv_sec = seconds;
	givenTime.tv_usec = milliseconds*1000;
	
	// addition
	timeradd(&timerSpeed, &givenTime, &timerSpeed);
}

bool Entity::getTimerSpeed()
{
	timeval currentTime;
	gettimeofday(&currentTime, NULL);
	
	if(timercmp(&timerSpeed, &currentTime, >) != 0)
		return true;
	else
		return false;
}

EntityType Entity::getType() 
{ 
	return type; 
}
