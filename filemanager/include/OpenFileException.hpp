#ifndef OPENFILEEXCEPTION_H
#define OPENFILEEXCEPTION_H


class OpenFileException
{
	public:
		virtual const char* what() const throw()
		{
			return "Impossible d'ouvrir le fichier (peut être un problème d'accès au dossier de téléchargement)";
		}
};

#endif // OPENFILEEXCEPTION_H
