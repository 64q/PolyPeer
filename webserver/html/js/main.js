/* Fichier principal JS */

/**
 * Environnement PolyPeer Client Web
 */
var PolyPeer = {

	/**
	 * Stats du serveur
	 */
	stats: null,
	
	/**
	 * Init de l'application web
	 */
	init: function(hash) {
		this.fillStats();
	},
	
	/**
	 * Initialise l'état du serveur dans le header
	 */
	fillStats: function() {
		Ajax.request('/ajax/get_stats', null, function(content) {
			var stats = JSON.parse(content);
			PolyPeer.stats = stats
			$("#state").innerHTML = printServerState(stats.state);
		}, function() {
			$("#state").innerHTML = printServerState("offline");
			PolyPeer.stats.state = "offline";
		});
	},
};

/**
 * Déclenché au chargement de la page
 */
window.addEventListener('load', function() {
	PolyPeer.init();
	HashNav.init();
	
	window.setInterval(function() {
		updateStatus();
	}, 2000);
	
});

function updateStatus() {
	PolyPeer.fillStats();
}

/* EOF */
