/* 
 * Fichier principal JS, initisalisation des bibliothèques
 * Quentin Lebourgeois - 2012
 */

/**
 * Déclenché au chargement de la page
 */
window.addEventListener('load', function() {
	PolyPeerJS.init();
	
	window.setInterval(function() { // Définition du rafraichissement du state
		PolyPeerJS.Utils.updateStatus();
	}, 2000);	
});

