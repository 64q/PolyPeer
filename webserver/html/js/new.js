/*
 * Fichier JS spécifique à la page de nouveau déploiement
 * Quentin Lebourgeois - 2012
 */
 
$('#new-deployment-form').addEventListener('submit', function(e) {
 	var name = $('#name');
 	var path = $('#path');
 	var cpath = $('#cpath');
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
 	} else if (name.value == "") {
 		notifyError('Veuillez donner un nom au déploiement');
 		error = true;
 	} else if (path.value == "") {
 		notifyError('Veuillez donner un chemin vers le fichier');
 		error = true;
 	} else if (cpath.value == "") {
 		notifyError('Veuillez donner un chemin où mettre le fichier chez le client');
 		error = true;
 	}
 	
 	if (!error) {
	 	Ajax.request('/ajax/new_deployment', 'name=' + name.value + '&spath=' + path.value + '&zones=' + str_zones + '&cpath=' + cpath.value, function(content) {
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
 
Ajax.request('/ajax/network', null, function(content) {
	var content = JSON.parse(content);
	var view = $('#zones-choice');
	for (var i = 0; i < content.length; i++) {
		if (content[i].type == "zone") {
			createInputZone(view, content[i]);
		}
	}
});

function createInputZone(parent, item) {
	
	var zone = document.createElement('p');
	var title = document.createElement('label');
	var input = document.createElement('input');
	
	input.type = "checkbox"; input.value = item.name;
	
	title.className = "checkbox";
	title.appendChild(input);
	title.appendChild(document.createTextNode(item.name));
	
	zone.appendChild(title);
	
	for (var i = 0; i < item.hosts.length; i++) {
		if (item.hosts[i].type == "zone") {
			createInputZone(zone, item.hosts[i]);
		}
	}

	parent.appendChild(zone);
}

