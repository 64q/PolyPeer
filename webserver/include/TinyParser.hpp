#ifndef __H_TINYPARSER__
#define __H_TINYPARSER__

#include <fstream>
#include <map>

/**
 * Classe gérant un petit parseur de page html spéciales
 * Pour apprendre à s'en servir, merci de regarder la documentation 
 * jointe avec le projet.
 */
class TinyParser
{
public:
	/**
	 * Constructeur du parseur
	 * @param filename
	 * 	chemin vers le fichier de template à charger
	 */
	TinyParser(std::string filename);
	
	/**
	 * Permet de charger un élement de template dans le parseur
	 * @param key
	 * 	variable contenue dans la template
	 * @param value
	 * 	la valeur qui va être mise à la place
	 */
	void inject(std::string, std::string);
	
	/**
	 * Génération du rendu dans une string
	 * @return string
	 * 	résultat généré par le parseur
	 */
	std::string render();
	
	/**
	 * Parse les variables contenues dans le fichier et les remplace
	 * dans l'attribut content
	 */
	void parse();

private:
	/**
	 * Fichier de la template
	 */
	std::ifstream file;
	
	/**
	 * Table de correspondance entre les variables et leur contenu.
	 */
	std::map<std::string, std::string> vars;
	
	/**
	 * Contenu de la page à rendre
	 */
	std::string content;
};

#endif
