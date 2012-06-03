/*
 * Exception lancée à l'initialisation de Mongoose
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
