#ifndef __H_ROUTES__
#define __H_ROUTES__

#include "WebRequest.hpp"

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
 * Route d'erreur interne
 * @param WebRequest
 * 	la requête fournie par le navigateur
 */
std::string internalerror_route(WebRequest& request);

/** 
 * Route de déploiement
 * @param WebRequest
 * 	la requête fournie par le navigateur
 */
std::string deployment_route(WebRequest& request);

/** 
 * Route des déploiements
 * @param WebRequest
 * 	la requête fournie par le navigateur
 */
std::string deployments_route(WebRequest& request);

/**
 * Route de l'admin serveur
 * @param WebRequest
 * 	la requête fournie par le navigateur
 */
std::string server_route(WebRequest& request);

/**
 * Route vers le stop du server
 * @param WebRequest
 * 	la requête fournie par le navigateur
 */
std::string stop_route(WebRequest& request);

/**
 * Route vers le restart du server
 * @param WebRequest
 * 	la requête fournie par le navigateur
 */
std::string restart_route(WebRequest& request);

/**
 * Route pour tout accès a autre chose qu'une route connue
 * Permet en autre de récupérer les scripts CSS, JS et les Images.
 * @param WebRequest
 * 	la requête fournie par le navigateur
 */
std::string ressource_route(WebRequest& request);

#endif
