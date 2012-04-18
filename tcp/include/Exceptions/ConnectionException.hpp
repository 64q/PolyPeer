
#include <exception>
using namespace std;

class ConnectionException: public exception
{

	public:
		virtual const char* what() const throw()
		{
		return "Erreur à la connection";
		}
};
