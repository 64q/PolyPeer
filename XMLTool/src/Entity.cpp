#include <iostream>

#include <Entity.hpp>

using namespace std;

Entity::Entity(const std::string& name, Entity* parent, int networkCapacity) :
	name(name), parent(parent), networkCapacity(networkCapacity)
{

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

int Entity::getNetworkCapacity()
{
	return networkCapacity;
}
