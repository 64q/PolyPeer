#ifndef __H_ZONE__
#define __H_ZONE__

#include <map>

#include <Entity.hpp>

class Zone : public Entity
{
private:
	std::map<std::string, Entity> entities;

public:
	/**
	 * Constructeur d'une zone
	 * @param string name
	 * 	nom de la zone
	 */
	Zone(const std::string& name);
};

#endif
