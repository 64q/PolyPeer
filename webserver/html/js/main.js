/* 
 * Fichier principal JS, initisalisation des bibliothèques
 * Quentin Lebourgeois - 2012
 */

/**
 * Déclenché au chargement de la page
 */
pp.ready(function() {
	pp.init();
	
	window.setInterval(function() { // Définition du rafraichissement du state
		pp.Utils.updateStatus();
	}, 2000);	
});

