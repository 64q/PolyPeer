#ifndef DISKFULLEXCEPTION_H
#define DISKFULLEXCEPTION_H

#include <exception>

class DiskFullException: public std::exception
{

	public:
		virtual const char* what() const throw()
		{
			return "Espace libre sur le disque dur insuffisant";
		}
};



#endif // DISKFULLEXCEPTION_H
