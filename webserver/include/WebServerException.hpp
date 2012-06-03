/*
 * Fichier contenant les routes pour gérer les appels clients web
 * Quentin Lebourgeois - 2012
 */
 
#include <exception>

using namespace std;

class WebServerException : public exception
{
public:
	virtual const char* what() const throw()
	{
			return "Impossible d'initialiser le serveur web integré !";
	}
};
