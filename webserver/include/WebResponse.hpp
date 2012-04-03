#ifndef __H__WEBRESPONSE__
#define __H__WEBRESPONSE__

/**
 * La WebResponse permet d'émettre une chaine de caractères
 * contenant les headers HTTP et le contenu. Cela sera directement
 * envoyé au navigateur dans la socket.
 */
class WebResponse
{
public:
	/**
	 * Constructeur de la WebResponse
	 * @param code
	 * 	code HTTP de la réponse
	 * @param content
	 * 	le contenu qui va être joint
	 */
	WebResponse(int code, std::string content);
	
	/**
	 * Récupère les données brutes qui seront envoyées
	 * @return string
	 * 	les données brutes envoyées par la socket
	 */
	std::string getRawData();
	
	/**
	 * Destructeur
	 */
	~WebResponse();
	
private:
	/**
	 * Code HTTP de la requête (important dans le header)
	 */
	int code;
	
	/**
	 * Taille du contenu envoyé au navigateur
	 */
	int size;
	
	/**
	 * Contenu brut envoyé au navigateur
	 */
	std::string content;
};

#endif
