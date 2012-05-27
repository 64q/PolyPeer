#ifndef __H_STATE__
#define __H_STATE__

/**
* Etat d'un Host
*/
enum HostState { DOWNLOAD=0, WAIT=1, OFFLINE=3, FULL=4 };

/**
* Etat du déploiement sur un Host donné
*/
enum HostDeployState { HDS_DOWNLOAD=0, HDS_WAIT=1, HDS_FINISH=2 };

/**
* Etat du déploiement dans sa globalité
*/
enum FileState { READY=0, DEPLOYMENT=1, FINISH=2, ERROR=3 };

/**
 * Récupère sous forme de chaine de texte l'état
 */
std::string getStringHostState(HostState state);

/**
 * Récupère sous forme de chaine de texte l'état
 */
std::string getStringHostDeployState(HostDeployState state);

/**
 * Récupère sous forme de chaine de texte l'état
 */
std::string getStringFileState(HostDeployState state);

#endif

