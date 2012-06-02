#ifndef __H_LOGGER__
#define __H_LOGGER__

// Library header
#include <sstream>
#include <fstream>

/**
 * Les terminaisons de ligne pour l'insertion par flux
 */
typedef enum
{
	endlog,
	endline,
} ELogAction;

/**
 * Les différents niveaux de logs
 */
typedef enum
{
	normal = 0,
	alert,
	error,
	critical,
	notice,
	debug,
} ELogImportance;
 
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
	Logger(const std::string&);
	
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
	void put(const std::string& type, const std::string& content);
	
	/**
	 * Insertion par flux dans le logger
	 */
	template<class T>Logger& operator<<(const T& value)
	{
		std::ostringstream oss;
		oss << value;
		stringSave += oss.str();
		return *this;
	}
	
	/**
	 * Actions spéciales sur le flux logger
	 */
	Logger& operator<<(const ELogAction logAct);
	
	/**
	 * Type de log
	 */
	Logger& operator<<(const ELogImportance logType);

	/**
	 * Récupérer la chaine de caracteres correspondant au type
	 * @param LogLevel
	 * 	niveau de la ligne de log
	 * @return string
	 *		la chaine associé au niveau
	 */
	std::string getType (const ELogImportance logType);
	
	/**
	 * Gère le mode d'output
	 * @param bool
	 * 	le mode d'affichage (true = cout + fichier, false = fichier)
	 */
	void setVerboseMode(bool mode) { verbose = mode; }
	
	/**
	 * Retourne l'état du mode d'affichage
	 * @return bool
	 * 	le mode d'affichage
	 */
	bool getVerboseMode() const { return verbose; }
	
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

	/**
	 * Chaine temporaire de sauvegarde pour le flux
	 */
	std::string stringSave;

	/**
	 * sauvegarde du type temporaire
	 */
	ELogImportance typeSave;

	/**
	 * Mode du débugger
	 */
	bool verbose;
};

#endif
