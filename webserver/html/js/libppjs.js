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
	pages: "/pages",
	js: "/js",
	ajax: "/ajax",
	stats: null,
	
	init: function() {
		this.Utils.updateStatus();
		this.HashNav.init(this.HashRoutes, this.HashRoutes.home);
	},
};

/**
 * Fonctions utilitaires intégrées
 */
PolyPeerJS.Utils = {
	callPage: function(file, callback) {
		PolyPeerJS.Ajax(PolyPeerJS.pages + '/' + file, null, function(content) {
			$('#content').text(content); callback();
		}, function(){}, false);
	},
	
	load: function(file) {
		var scriptElement = document.createElement('script');
		scriptElement.src = PolyPeerJS.js + '/' + file;
		$('body').appendChild(scriptElement);
	},
	
	updateStatus: function() {
		PolyPeerJS.Ajax(PolyPeerJS.ajax + '/get_stats', null, 
			function(content) {
				PolyPeerJS.stats = content;
				$("#state").text(printServerState(content.state));
			}, 
			function() { // Le serveur ne répond pas, on le considère offline
				PolyPeerJS.stats.state = "offline";
				$("#state").text(printServerState(content.state));
			}
		);
	},
	
	error: function(type) {
		PolyPeerJS.Utils.callPage(type + '.html', function(){});
	},
};

/** 
 * Routes vers les différentes pages
 */
PolyPeerJS.HashRoutes = {
	home: function() {
		PolyPeerJS.Utils.callPage('home.html', function() {
			$('#overview').text( // Définition du contenu de l'aperçu rapide
				'<dl>' +
					'<dt>Etat du serveur</dt><dd>L\'état du serveur est ' + printServerState(PolyPeerJS.stats.state) + '</dd>' +
					'<dt>Nombre de déploiements en cours</dt><dd>Il y a actuellement ' + PolyPeerJS.stats.count_deployments + ' en cours</dd>' +
					'<dt>Nombre d\'entitées sur le réseau</dt><dd>Il y a ' + PolyPeerJS.stats.count_hosts + ' hotes sur le réseau</dd>' +
				'</dl>'
			);
		});
	},
	
	add: function() {
		PolyPeerJS.Utils.callPage('add.html', function() {
			PolyPeerJS.Utils.load('add.js');
		});
	},
	
	host: function() {
		PolyPeerJS.Utils.callPage('host.html', function() {
			PolyPeerJS.Utils.load('host.js');
		});
	},
	
	network: function() {
		PolyPeerJS.Utils.callPage('network.html', function() {
			PolyPeerJS.Utils.load('network.js');
		});
	},
	
	deployments: function() {
		PolyPeerJS.Utils.callPage('deployments.html', function() {
			PolyPeerJS.Utils.load('deployments.js');
		});
	},
	
	deployment: function() {
		PolyPeerJS.Utils.callPage('deployment.html', function() {
			PolyPeerJS.Utils.load('deployment.js');
		});
	},
	
	doc: function() {
		PolyPeerJS.Utils.callPage('doc.html', function(){});
	},
};

/**
 * Abbréviation pour PolyPeerJS
 */
var pp = PolyPeerJS;
