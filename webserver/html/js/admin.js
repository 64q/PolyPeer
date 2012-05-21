/*
 * Fichier JS spécifique à l'admin page
 * Quentin Lebourgeois - 2012
 */

$('#stop-button').addEventListener('click', function() {
	if (confirm('Etes-vous sûr de vouloir stopper le serveur ?')) {
		Ajax.request('/ajax/stop_srv', null, function(content) {
			if (content == "1") {
				notifySuccess("Le serveur a été arrêté avec succès");
			} else {
				notifyError("Le serveur a été arrêté avec succès");
			}
		});
	}
});

$('#restart-button').addEventListener('click', function() {
	if (confirm('Etes-vous sûr de vouloir redémarrer le serveur ?')) {
		Ajax.request('/ajax/restart_srv', null, function(content) {
			if (content == "1") {
				notifySuccess("Le serveur a été redémarré avec succès");
			} else {
				notifyError("Le serveur a été redémarré avec succès");
			}
		});
	}
});

$('#pause-button').addEventListener('click', function() {
	if (confirm('Etes-vous sûr de vouloir mettre en pause le serveur ?')) {
		Ajax.request('/ajax/pause_srv', null, function(content) {
			if (content == "1") {
				notifySuccess("Le serveur a été mis en pause avec succès");
			} else {
				notifyError("Le serveur n'a pas été mis en pause");
			}
		});
	}
});
