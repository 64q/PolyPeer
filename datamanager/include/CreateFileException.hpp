#ifndef CREATEFILEEXCEPTION_H
#define CREATEFILEEXCEPTION_H

/**
 * Exception qui est lancée lorsque le fichier de déploiement n'a pas pu être correctement créé
 */

class CreateFileException
{
	public:
		virtual const char* what() const throw()
		{
			return "Problème lors de la création du déploiement, fichier inexistant";
		}
};

#endif // CREATEFILEEXCEPTION_H
