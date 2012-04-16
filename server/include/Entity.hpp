#ifndef __H_ENTITY__
#define __H_ENTITY__

/**
 * Une entité sur le réseau
 */
class Entity
{
public:
	/**
	 * Contructeur d'une entité
	 * @param string name
	 * 	nom de l'entité
	 */
	Entity(const std::string& name);
	
protected:
	/**
	 * Nom de l'entité
	 */
	std::string name;
};

#endif
