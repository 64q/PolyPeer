#ifndef __H_LOGGER__
#define __H_LOGGER__

#include <fstream>

/**
 * Le logger permet d'enregistrer dans un fichier toute trace textuelle émise par
 * les serveurs afin de pouvoir traiter les éventuelles erreurs/informations.
 */
class Logger
{
public:
	/**
	 * Constructeur de logger
	 * @param char*
	 * 	chemin vers le fichier de log (créé s'il n'existe pas, sinon
	 * 	il écrit à la suite dedans)
	 */
	Logger(const char* path);
	
	/**
	 * Destructeur de logger (ferme le fichier)
	 */
	virtual ~Logger();
	
	/** 
	 * Insère une ligne dans le logger
	 * @param char*
	 * 	le type de message a enregister (error, notice, ...)
	 * @param char*
	 * 	le contenu à enregister
	 */
	void put(const char* type, const char* content);
	
	/**
	 * Récupère le contenu du fichier de log dans une chaine
	 * @return string
	 * 	contenu du fichier de log
	 */
	std::string getContent();
	
private:
	/*
	 * Le constructeur par copie et l'opérateur = sont privés
	 * pour éviter toute recopie du logger (unique sur chaque fichier)
	 */
	Logger(const Logger&);
	Logger& operator=(const Logger&);
	
	/**
	 * ofstream sur le fichier où l'on enregistre
	 */
	std::ofstream file;
};

#endif
