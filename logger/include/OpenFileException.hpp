#include <exception>

using namespace std;

class OpenFileException : public exception
{

	public:
		virtual const char* what() const throw()
		{
			return "Impossible d'ouvrir le fichier cible";
		}
};
