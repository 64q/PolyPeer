#include <iostream>
#include <cmath>
#include <Entity.hpp>

using namespace std;

Entity::Entity(const std::string& name, Entity* parent, int networkCapacity) :
	name(name), parent(parent), networkCapacity(networkCapacity)
{
	setTimerSpeed(0, 0);
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

void Entity::calculNewTimerSpeed(unsigned int packetSizeInOctet)
{
	// calcul
	unsigned int conversionStoMc = 1000000; // pour faire le découpage dans le set (sec, mc)
	// la taille du packet est en otets
	unsigned int capacite = abs(this->getNetworkCapacity()); // en Ko pas sec
	// temps nécessaire pour envoyer le paquet en microseconde
	unsigned int neededTimeMc = (packetSizeInOctet*1000)/capacite; 
	// mise en place du temps d'attente pour l'envoi du prochain paquet
	this->setTimerSpeed(neededTimeMc/conversionStoMc, neededTimeMc%conversionStoMc);
}

void Entity::setTimerSpeed(int seconds, int microseconds)
{
	// remise à jour du time
	gettimeofday(&timerSpeed, NULL);
	
	// récupération du time en paramètre
	timeval givenTime;
	givenTime.tv_sec = seconds;
	givenTime.tv_usec = microseconds;
	
	// addition
	timeradd(&timerSpeed, &givenTime, &timerSpeed);
}

bool Entity::getTimerSpeed()
{
	timeval currentTime;
	gettimeofday(&currentTime, NULL);
	if(timercmp(&timerSpeed, &currentTime, <) != 0)
		return true;
	else
		return false;
}

EntityType Entity::getType() 
{ 
	return type; 
}
