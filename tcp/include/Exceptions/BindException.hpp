
#include <exception>
using namespace std;

class BindException: public exception
{

	public:
		virtual const char* what() const throw()
		{
		return "Erreur pendnt le bind";
		}
};

