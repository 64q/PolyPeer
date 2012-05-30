#ifndef CREATEFILEEXCEPTION_H
#define CREATEFILEEXCEPTION_H


class CreateFileException
{
	public:
		virtual const char* what() const throw()
		{
			return "Problème lors de la création du déploiement, fichier inexistant";
		}
};

#endif // CREATEFILEEXCEPTION_H
