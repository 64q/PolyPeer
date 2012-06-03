/*
 * Logger
 * Lebourgeois Quentin - 2012
 */

#ifndef __H_OPENLOGGEREXCEPTION__
#define __H_OPENLOGGEREXCEPTION__

#include <exception>

class OpenLoggerException : public std::exception
{

	public:
		virtual const char* what() const throw()
		{
			return "Impossible d'ouvrir le fichier cible";
		}
};

#endif
