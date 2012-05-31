/*
 * Lib PolyPeer JS
 * 
 * Bibliothèque PolyPeer en JavaScript pour interfacer le serveur 
 * avec le site web.
 *
 * Quentin Lebourgeois - 2012
 *
 */
 
/**
 * PolyPeerJS lib - Objet assurant la gestion des actions
 * du serveur web.
 */
var PolyPeerJS = {
	/**
	 * Chemin des pages web à charger
	 */
	pages: "/pages",
	
	/**
	 * Chemin des scripts JS
	 */
	js: "/js",
	
	/**
	 * Route vers les requêtes ajax (nécessaire pour interroger le srv)
	 */
	ajax: "/ajax",
	
	/**
	 * Stats courantes du serveur (état, nb déploiements...)
	 */
	stats: null,
	
	/**
	 * Etat de la navigation (changement de page, nécessaire pour refresh des infos)
	 */
	hasChanged: false,
	
	/** 
	 * Initialisation de l'environnement, recherche du status et
	 * préparation HashNav (reprise sur la bonne page)
	 */
	init: function() {
		this.Utils.updateStatus();
		this.HashNav.init(this.HashRoutes, this.HashRoutes.home);
	},
	
	/**
	 * Cette fonction ne déclenchera le callback que lorsque la page sera chargée
	 * @param callback
	 * 	fonction a executé une fois la page chargée
	 */
	ready: function(callback) {
		window.addEventListener('load', callback);
	},
};

/**
 * Fonctions utilitaires intégrées
 */
PolyPeerJS.Utils = {
	/**
	 * Appel d'une page html sur le serveur
	 * @param file
	 * 	chemin vers la page (ajout automatique de '/pages')
	 * @param callback
	 * 	fonction a exectuer au chargement
	 */
	callPage: function(file, callback) {
		PolyPeerJS.Ajax(PolyPeerJS.pages + '/' + file, null, function(content) {
			$('#content').text(content); callback();
		}, function(){}, false);
	},
	
	/**
	 * Chargement d'un fichier JS dans le DOM de la page
	 * Le fichier est alors placé en fin de page.
	 * @param file
	 * 	chemin du script js (préfixé automatiquement de '/js')
	 */
	load: function(file) {
		var scriptElement = document.createElement('script');
		scriptElement.src = PolyPeerJS.js + '/' + file;
		$('body').appendChild(scriptElement);
	},
	
	/**
	 * Mise à jour du state, appelé à intervalles réguliers
	 */
	updateStatus: function() {
		PolyPeerJS.Ajax(PolyPeerJS.ajax + '/get_stats', null, 
			function(content) {
				if (PolyPeerJS.stats != null && PolyPeerJS.stats.state == "offline") {
					PolyPeerJS.HashNav.onChange();
				}
				PolyPeerJS.stats = content;
				$("#state").text(printServerState(content.state));
			}, 
			function() { // Le serveur ne répond pas, on le considère offline
				PolyPeerJS.stats.state = "offline";
				$("#state").text(printServerState(content.state));
				PolyPeerJS.Utils.serverDown();
			}
		);
	},
	
	/**
	 * Fonction permettant de générer une page pour notifier que le
	 * serveur est éteint (nécessaire car nav. sans rechargement)
	 */
	serverDown: function() {
		$('#content').text(
			'<div class="page-header">'+
				'<h1>Aucune réponse</h1>'+
			'</div>'+
			'<div class="alert alert-error">'+
				'<strong>Alerte !</strong> Le serveur ne répond pas !'+
			'</div>'
		);
	},
	
	/** 
	 * Fonction pour déclencher une erreur précise sur le serveur
	 * selon son type.
	 * @param type
	 * 	type de l'erreur à déclencher
	 */
	error: function(type) {
		PolyPeerJS.Utils.callPage(type + '.html', function(){});
	},
};

/** 
 * Routes vers les différentes pages
 */
PolyPeerJS.HashRoutes = {
	/**
	 * Route par défaut sur le serveur web ici, page d'accueil
	 */
	home: function() {
		PolyPeerJS.Utils.callPage('home.html', function() {
			// Mise à jour données
			PolyPeerJS.Utils.updateStatus();
			
			$('#overview').text( // Définition du contenu de l'aperçu rapide
				'<dl>' +
					'<dt>Etat du serveur</dt><dd>L\'état du serveur est ' + printServerState(PolyPeerJS.stats.state) + '</dd>' +
					'<dt>Nombre de déploiements en cours</dt><dd>Il y a actuellement ' + PolyPeerJS.stats.count_deployments + ' en cours</dd>' +
				'</dl>'
			);
		});
	},
	
	/**
	 * Route qui déclenche la page d'ajout d'un déploiement
	 */
	add: function() {
		PolyPeerJS.Utils.callPage('add.html', function() {
			PolyPeerJS.Utils.load('add.js');
		});
	},
	
	/**
	 * Route qui déclenche la page de vue d'un hote
	 */
	host: function() {
		PolyPeerJS.Utils.callPage('host.html', function() {
			PolyPeerJS.Utils.load('host.js');
		});
	},
	
	/**
	 * Route qui déclenche la page de visualisation du réseau
	 */
	network: function() {
		PolyPeerJS.Utils.callPage('network.html', function() {
			PolyPeerJS.Utils.load('network.js');
		});
	},
	
	/**
	 * Route qui déclenche la page des déploiements
	 */
	deployments: function() {
		PolyPeerJS.Utils.callPage('deployments.html', function() {
			PolyPeerJS.Utils.load('deployments.js');
		});
	},
	
	/**
	 * Route qui déclenche la page de vue d'un déploiement
	 */
	deployment: function() {
		PolyPeerJS.Utils.callPage('deployment.html', function() {
			PolyPeerJS.Utils.load('deployment.js');
		});
	},
	
	/**
	 * Route qui déclenche la page de vision de la doc
	 */
	doc: function() {
		PolyPeerJS.Utils.callPage('doc.html', function(){});
	},
	
	/**
	 * Route qui déclenche la page des crédits
	 */
	credits: function() {
		PolyPeerJS.Utils.callPage('credits.html', function(){});
	},
	
	log: function() {
		PolyPeerJS.Utils.callPage('log.html', function() {
			PolyPeerJS.Utils.load('log.js');
		});
	},
};

/**
 * Abbréviation pour PolyPeerJS, utilisé dans les scripts JS chargés
 * dynamiquement dans le DOM (network, host, etc)
 */
var pp = PolyPeerJS;

/**
 * Raccourci pour accès aux fonctions utilitaires
 */
var ppu = PolyPeerJS.Utils;

/**
 * Raccourci pour accès à la fonction d'Ajax
 */
var ppa = PolyPeerJS.Ajax;
