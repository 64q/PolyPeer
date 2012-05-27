#ifndef __H_STATE__
#define __H_STATE__

#include <string>

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
enum FileState { READY=0, DEPLOYMENT=1, FINISH=2, F_PAUSE=3, F_ERROR=4 };

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
std::string getStringFileState(FileState state);

/**
 * Récupère le FIleState à partir d'une chaine de caractère
 */
FileState getFileStateString(std::string stringState);


#endif

