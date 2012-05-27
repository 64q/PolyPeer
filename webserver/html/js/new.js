/*
 * Fichier JS spécifique à la page de nouveau déploiement
 * Quentin Lebourgeois - 2012
 */
 
$('#new-deployment-form').addEventListener('submit', function(e) {
 	var name = $('#name');
 	var path = $('#path');
 	var error = false;
 	
 	var checkboxes = qsa('#new-deployment-form input[type="checkbox"]');
	var zones = [];
	
	for (var i = 0; i < checkboxes.length; i++) {
		if (checkboxes[i].checked) {
			zones.push(checkboxes[i].value);
		}
	}
	
	var str_zones = zones.join(',');
 	
 	if (zones.length == 0) {
 		notifyError('Veuillez cocher au moins une zone');
 		error = true;
 	} else if (name == "") {
 		notifyError('Veuillez donner un nom au déploiement');
 		error = true;
 	} else if (path == "") {
 		notifyError('Veuillez donner un chemin vers le fichier');
 		error = true;
 	}
 	
 	if (!error) {
	 	Ajax.request('/ajax/new_deployment', 'name=' + name.value + '&path=' + path.value + '&zones=' + str_zones, function(content) {
	 		var content = JSON.parse(content);
	 		
	 		if (content.state == "done") {
	 			notifySuccess('Création du déploiement exectuée.');
	 		} else {
	 			notifyError('Impossible de créer le nouveau déploiement');
	 		}
	 	});
	}
 	
 	e.preventDefault();
 });
