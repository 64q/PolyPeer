/*
 * Fichier JS spécifique à la page de nouveau déploiement
 * Quentin Lebourgeois - 2012
 */
 
$('#new-deployment-form').addEventListener('submit', function(e) {
 	var name = $('#name');
 	var path = $('#path');
 	
 	var checkboxes = qsa('#new-deployment-form input[type="checkbox"]');
	var checked = '';
	var zones = [];
	
	for (var i = 0; i < checkboxes.length; i++) {
		if (checkboxes[i].checked) {
			zones.push(checkboxes[i].value);
		}
	}
	
	var str_zones = zones.join(',');
 	
 	Ajax.request('/ajax/new_deployment', 'name=' + name.value + '&path=' + path.value + '&zones=' + str_zones, function(content) {
 		var content = JSON.parse(content);
 		
 		notifySuccess('Création du déploiement exectuée.');
 	});
 	
 	e.preventDefault();
 });
