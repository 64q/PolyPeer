#ifndef __H_ZONE__
#define __H_ZONE__

#include <map>

#include <Entity.hpp>
 
class Zone : public Entity
{
public:

	/**
	 * Constructeur d'une zone
	 * @param name
	 *	 nom de la zone
	 * @param parent
	 *	 pointeur vers l'entité qui contient la zone
	 * @param networkCapacity
	 *	 capacité réseau du lien entre la zone et son père
	 */
	Zone(const std::string& name, Entity* parent, int networkCapacity);
	~Zone();
	void addDeploymentState(const int, File*, HostDeployState hds);
	DeploymentState* getDeploymentState(int idFile);
	std::map<std::string, Entity*>* getEntities();
	std::vector<DeploymentState>* getDeploys();
	std::string getIP();
	std::string getMac();
	std::string getMask();
	HostState getHostState();
	void setHostState(HostState);
	void setTimerState();
	double getTimerState();
	
private:

	/**
	 * Structure contenant l'ensemble des entités (Zones ou Hosts) que contient la Zone
	 */
	std::map<std::string, Entity*> entities;

	
};

#endif
