#ifndef __H_HOST__
#define __H_HOST__

#include <vector>
#include <map>
#include <string>

#include <Entity.hpp>

/**
 * Classe contenant l'ensemble des informations d'un client
 */
 
class Host : public Entity
{	
public:

	/**
	 * Constructeur d'un client
	 * @param name
	 *	 nom du client
	 * @param parent
	 *	 pointeur vers l'entité qui contient le client
	 * @param networkCapacity
	 *	 capacité réseau entre le client et son père
	 * @param ip
	 *	 adresse ip du client
	 * @param mac
	 *	 adresse mac du client
	 */
	Host(const std::string& name, Entity* parent, int networkCapacity, const std::string& ip, const std::string& mac);
	~Host();
	void addDeploymentState(const int cid, File* file, HostDeployState hds);
	DeploymentState* getDeploymentState(int idFile);
	std::vector<DeploymentState>* getDeploys();
	std::string getIP();
	std::string getMac();
	HostState getHostState();
	void setHostState(HostState);
	std::map<std::string, Entity*>* getEntities();
	void setTimerState();
	double getTimerState();
	
private:
	
	/**
	 * Etat courant du client
	 */
	HostState hostState;
	
	/**
	 * Timer pour vérifier à quelle date le client a été contacté
	 */
	time_t timerState;
	
	/**
	 * Adresse ip du client
	 */
	std::string ip;
	
	/**
	 * Adresse mac du client
	 */
	std::string mac;
	
	/**
	 * Structure contenant l'ensemble des informations relatives à chaque fichier que doit télécharger
	 * le client
	 */
	std::vector<DeploymentState> deploys;

};

#endif
