var Ajax = {
	/**
	 * Fonction d'appel AJAX
	 * @param file
	 * 	fichier à appeler
	 * @param params
	 * 	paramètres à envoyer
	 * @param callback
	 * 	fonction executée à la fin de l'appel
	 */
	request: function(target, params, callback) {
		var xhr = this.getXMLHttpRequest();

		xhr.onreadystatechange = function() {
			if (xhr.readyState == 4 && (xhr.status == 200 || xhr.status == 0)) {
				callback(xhr.responseText);
			}
		};

		xhr.open("GET", "/ajax/" + target + "?" + params, true);
		xhr.send(null);
	},

	/**
	 * Fonction XMLHttpRequest
	 * @return xhr
	 */
	getXMLHttpRequest: function() {
		var xhr = null;

		if (window.XMLHttpRequest || window.ActiveXObject) {
			if (window.ActiveXObject) {
				try {
					xhr = new ActiveXObject("Msxml2.XMLHTTP");
				} catch(e) {
					xhr = new ActiveXObject("Microsoft.XMLHTTP");
				}
			} else {
				xhr = new XMLHttpRequest(); 
			}
		} else {
			alert("Votre navigateur ne supporte pas l'objet XMLHTTPRequest...");
			return null;
		}

		return xhr;
	}
};
