/*
 * Fichier JS spécifique à la page de nouveau déploiement
 * Quentin Lebourgeois - 2012
 */
 
$('#new-deployment-form').addEventListener('submit', function(e) {
 	var name = $('#name');
 	var path = $('#path');
 	
 	var checkboxes = qsa('#new-deployment-form input[type="checkbox"]');
	var checked = '';
	for (var i = 0; i < checkboxes.length; i++) {
		if (checkboxes[i].checked) {
			checked += checkboxes[i].value;
			if (i != (checkboxes.length - 1)) {
				checked += ':';
			}
		}
	}
 	
 	Ajax.request('/ajax/new_deployment', 'name=' + name.value + '&path=' + path.value + '&zones=' + checked, function(content) {
 		var content = JSON.parse(content);
 		
 		notifySuccess('Création du déploiement exectuée.');
 	});
 	
 	e.preventDefault();
 });
