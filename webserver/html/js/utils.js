/*
 * Utilitaires JS
 * Définition d'une partie de PolyPeerJS :
 * - HashNav
 * - Ajax
 * Quentin Lebourgeois - 2012
 */

/**
 * Raccourcissement de la fonction querySelector, à laquelle j'ai
 * ajouté une fonction text() permettant d'inserer du contenu HTML
 * @param selector
 * 	un selecteur (#div, .class, elem)
 * @param el
 *		un élement optionnel (par défaut document)
 */
function $(selector, el) {
	if (!el) {
		el = document;
	}
	
	this.el = el.querySelector(selector);
	
	if (this.el !=  undefined) {
		this.el.text = function(content) {
			this.innerHTML = content;
		}
	}
	
	return this.el;
}

/**
 * Wrapper pour querySelectorAll
 * @param selector
 * 	un selecteur (#div, .class, elem)
 * @param el
 *		un élement optionnel (par défaut document)
 */
function $$(selector, el) {
	if (!el) {el = document;}
	return Array.prototype.slice.call(el.querySelectorAll(selector));
}

/**
 * Utilitaire de gestion des requêtes Ajax selon le principe suivant :
 * Requête GET sur le serveur avec deux fonctions de callback
 * Une success, déclenchée quand succès de la requête, sinon
 * Une error, déclenchée quand echec de la requête
 * @param file
 * 	chemin vers le serveur
 * @param params
 * 	paramètres de la requête
 * @param success
 * 	callback en cas de succès
 * @param error
 * 	callback en cas d'echec (optionnel)
 */
PolyPeerJS.Ajax = function(file, params, success, error, isParsable) {
	var xhr = new XMLHttpRequest();
	var sent = file;
	
	// Lecture des paramètres optionnels
	if (params != null) {
		sent += '?' + params;
	}
	
	if (isParsable == null) {
		isParsable = true;
	}
	
	if (error == null) {
		error = PolyPeerJS.Utils.serverDown;
	}
	// Fin lecture paramètres
	
	xhr.onabort = xhr.onerror = function() { // Défintion du callback en cas d'erreur de la requete
		error();
	};
	
	xhr.onreadystatechange = function() {
		if (xhr.readyState == 4 && xhr.status == 200) {
			// Les données reçues sont du JSON
			if (isParsable) {
				var parsed = JSON.parse(xhr.responseText);
				if (parsed.state != undefined && parsed.state == "error" && error != null) {
					error();
				} else {
					success(parsed);
				}
			} 
			// Sinon c'est autre chose, on ne parse pas, on déclenche forcément la fn de succès
			else {
				success(xhr.responseText);
			}
		} else if (xhr.readyState == 4 && xhr.status == 404) {
			PolyPeerJS.Utils.error('404'); // Erreur 404, page introuvable
		}
	};
	
	xhr.open('GET', sent);
	xhr.send(null);
};

/**
 * PolyPeerJS HashNav, gestion complète d'une navigation par hash
 * Simple et flexible.
 */
PolyPeerJS.HashNav = {
	/**
	 * Page courante
	 */
	current: null,
	
	/**
	 * Variables paramètres (après la page courante #!/page/param1/param2)
	 */
	vars: null,
	
	/**
	 * Fonctions de callback chargées 
	 */
	callbacks: null,
	
	/**
	 * Racine de la navigation
	 */
	root: null,
	
	/**
	 * Initialisation de la HashNav, chargement des callbacks
	 * et définition de la page courante
	 * @param cbs
	 * 	les callbacks de la HashNav
	 * @param root
	 * 	un callback vers la racine (page d'accueil)
	 */
	init: function(cbs, root) {
		this.callbacks = cbs;
		this.root = root;
		
		// init de la nav
		window.addEventListener('hashchange', this.onChange);
		this.onChange(); // Forcage d'analyse au chargement
	},
	
	/**
	 * Cette fonction est appelée a chaque changement sur la page
	 * On va alors regarder le Hash et lancer la requête
	 */
	onChange: function() {
		var addr = location.hash;
		var that = PolyPeerJS.HashNav;
		
		if (addr.length > 1) {
			if (addr.charAt(1) == '!') { // analyse des adresses commençant par "#!/"
				that.vars = addr.split('/'); that.vars.shift()
				that.current = that.vars.shift();
				
				if (that.callbacks[that.current] != undefined) {
					that.callbacks[that.current](that.vars);
				} else {
					that.notFound();
				}
				
				PolyPeerJS.hasChanged = true;
			}
		} else {
			that.root();
		}
	},
	
	/**
	 * Méthode appelée uniquement si l'analyseur n'a pas trouvé de route
	 */
	notFound: function() {
		PolyPeerJS.Utils.error('404'); // Lance une erreur 404
	},
};

/**
 * Affichage d'un succès
 * @param msg
 * 	un message à transmettre
 */
function notifySuccess(msg) {
	$('#notifs').innerHTML = '<div class="alert alert-success"><strong>Succès !</strong> ' + msg + '</div>';
}

/**
 * Affichage d'une erreur
 * @param msg
 * 	un message à transmettre
 */
function notifyError(msg) {
	$('#notifs').innerHTML = '<div class="alert alert-error"><strong>Erreur !</strong> ' + msg + '</div>';
}

/**
 * Affichage host state formaté
 * @param state
 * 	etat de l'hote
 */
function printHostState(state)
{
	var result;
	
	switch (state)
	{
		case 'download':
			result = '<span class="status download">En téléchargement</span>';
			break;
		case 'wait':
			result = '<span class="status wait">En attente</span>';
			break;
		case 'offline':
			result = '<span class="status offline">Hors ligne</span>';
			break;
		default:
			result = '<span class="status undefined">Non défini</span>';
	}
	
	return result;
}

/**
 * Affichage deployment state formaté
 * @param state
 * 	etat du déploiement chez l'hote
 */
function printDeployState(state)
{
	var result;
	
	switch (state)
	{
		case 'wait':
			result = '<span class="status wait">En attente</span>';
			break;
		case 'finished':
			result = '<span class="status finished">Fini</span>';
			break;
		case 'init':
			result = '<span class="status init">Initialisation</span>';
			break;
		case 'disk full':
			result = '<span class="status full">Disque plein</span>';
			break;
		default:
			result = '<span class="status undefined">Non défini</span>';
	}
	
	return result;
}

/**
 * Affichage file state formaté
 * @param state
 * 	etat du déploiement
 */
function printFileState(state)
{
	var result;
	
	switch (state)
	{
		case 'ready':
			result = '<span class="status ready">Prêt</span>';
			break;
		case 'deployment':
			result = '<span class="status deploy">En déploiement</span>';
			break;
		case 'finished':
			result = '<span class="status finished">Fini</span>';
			break;
		case 'error':
			result = '<span class="status err">En erreur</span>';
			break;
		case 'pause':
			result = '<span class="status pause">En pause</span>';
			break;
		default:
			result = '<span class="status undefined">Non défini</span>';
	}
	
	return '<span class="status">' + result + '</span>';
}

/** 
 * Affichage formaté de l'état du serveur
 * @param state
 * 	l'état courant du serveur
 */ 
function printServerState(state)
{
	var result;
	
	if (state == "online") {
		result = '<span class="server-state online">En ligne</span>';
	} else {
		result ='<span class="server-state offline">Hors ligne</span>';
	}
	
	return result;
}
