/*
 * Fichier contenant les routes pour gérer les appels clients web
 * Quentin Lebourgeois - 2012
 */
 
#ifndef __H__ROUTES__
#define __H__ROUTES__

#include <Entity.hpp>

/**
 * Fonction utile pour récupérer les données envoyées par le client
 */
void get_qsvar(const mg_request_info *request_info, const char *name, char *dst, size_t dst_len);

/**
 * Route gérant l'affichage des déploiements
 */
void deployments_route(mg_connection* conn, const mg_request_info* request_info);

/**
 * Route pour récupérer l'état du serveur
 */
void get_stats_route(mg_connection* conn, const mg_request_info* request_info);

/**
 * Route pour récupérer l'état d'un client
 */
void get_host_route(mg_connection* conn, const mg_request_info* request_info);

/**
 * Route pour afficher un déploiement
 */
void deployment_route(mg_connection* conn, const mg_request_info* request_info);

/**
 * Fonction utilitaire pour l'affichage du réseau
 * Elle permet notamment d'afficher les entités contenues dans l'entité courante
 * Afin d'afficher le réseau sous forme d'arbre par la suite.
 * @param conn connexion mongoose
 * @param entity entité courante
 */
void displayEntity(mg_connection* conn, Entity* entity);

/**
 * Route pour afficher la topologie du réseau
 */
void network_route(mg_connection* conn, const mg_request_info* request_info);

/**
 * Route pour créer un déploiement
 */
void new_deployment_route(mg_connection* conn, const mg_request_info* request_info);

/**
 * Route pour pauser le serveur
 */
void pause_deployments_route(mg_connection* conn, const mg_request_info* request_info);

/**
 * Route pour delete un déploiement
 */
void delete_deployment_route(mg_connection* conn, const mg_request_info* request_info);

/**
 * Route pour pauser un déploiement
 */
void pause_deployment_route(mg_connection* conn, const mg_request_info* request_info);

/**
 * Route pour remettre en route un déploiement
 */
void unpause_deployment_route(mg_connection* conn, const mg_request_info* request_info);

/** 
 * Route pour accéder à un fichier de log
 * Remarque importante : le format de sortie n'est pas du JSON car les logs contiennent des \n
 * qui ne sont pas parsables par JSON.parse en JS. On retourne donc du texte brut.
 */
void log_route(mg_connection* conn, const mg_request_info* request_info);

#endif
