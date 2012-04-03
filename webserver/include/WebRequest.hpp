#ifndef __H__WEBREQUEST__
#define __H__WEBREQUEST__

#include <map>

/**
 * La classe WebRequest fourni une interface complète pour l'interprétation
 * d'un paquet HTTP envoyé par le navigateur du client. Il décompose les headers
 * afin d'en extraire les données utiles au programmeur.
 */
class WebRequest
{
public:
	/**
	 * Constructeur d'une WebRequest
	 * @param raw
	 * 	les données brutes reçues du navigateur
	 */
	WebRequest(char* raw);
	
	/**
	 * Destructeur
	 */
	~WebRequest();
	
	/**
	 * Renvoie la méthode utilisée
	 * @return string
	 * 	valeur peut être "GET", "POST", etc.
	 */
	std::string getMethod();
	
	/**
	 * Renvoie la route ciblée.
	 * @return string
	 * 	route ciblée par le navigateur
	 */
	std::string getTarget();
	
	/**
	 * Renvoie le paramètre GET contenu dans la barre d'adresse
	 * @param string
	 * 	clé
	 * @return string
	 *		renvoie la valeur associée à la clé (undefined si elle n'existe pas)
	 */
	std::string getParam(std::string key);
	
private:
	/**
	 * Contient la méthode (GET, POST, etc.)
	 */
	std::string method;
	
	/**
	 * Contient la cible (ex.: /, /login, /server, etc.)
	 */
	std::string target;
	
	/**
	 * Table associative avec en clé le paramtère et en valeur la valeur de ce paramètre
	 * Rempli avec les variables données après le "?" dans la barre d'adresse.
	 */
	std::map<std::string, std::string> params;
};

#endif
