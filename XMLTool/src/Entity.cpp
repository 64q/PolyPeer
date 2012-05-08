#include <iostream>

#include "../include/Entity.hpp"

using namespace std;

Entity::Entity(const std::string& name) :
	name(name)
{

}

Entity::~Entity()
{
}

std::string Entity::getName()
{
	return name;
}

