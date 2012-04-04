#ifndef __H_ROUTES__
#define __H_ROUTES__

/**
 * Route par défaut
 * @param WebRequest
 * 	la requête fournie par le navigateur
 */
std::string default_route(WebRequest& request);

/**
 * Route not found
 * @param WebRequest
 * 	la requête fournie par le navigateur
 */
std::string notfound_route(WebRequest& request);

/** 
 * Route de déploiement
 * @param WebRequest
 * 	la requête fournie par le navigateur
 */
std::string deployment_route(WebRequest& request);

/**
 * Route de l'admin serveur
 * @param WebRequest
 * 	la requête fournie par le navigateur
 */
string server_route(WebRequest& request);

/**
 * Route vers le stop du server
 * @param WebRequest
 * 	la requête fournie par le navigateur
 */
string stop_route(WebRequest& request);

/**
 * Route vers le restart du server
 * @param WebRequest
 * 	la requête fournie par le navigateur
 */
string restart_route(WebRequest& request);

#endif
