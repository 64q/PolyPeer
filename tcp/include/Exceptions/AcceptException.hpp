#include <exception>
using namespace std;

class AcceptException: public exception
{

	public:
		virtual const char* what() const throw()
		{
			return "Impossible de recevoir des connections ( accept() )";
		}
};


