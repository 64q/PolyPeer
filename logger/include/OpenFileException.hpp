#include <exception>

class OpenFileException : public std::exception
{

	public:
		virtual const char* what() const throw()
		{
			return "Impossible d'ouvrir le fichier cible";
		}
};
