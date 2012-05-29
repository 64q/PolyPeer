/*
 * Fichier JS spécifique à la page des déploiements
 * Quentin Lebourgeois - 2012
 */
 
 function createDeploymentLine(item)
{
	var line = document.createElement('tr');
	var id = document.createElement('td');
	var date = document.createElement('td');
	var name = document.createElement('td');
	var state = document.createElement('td');
	var actions = document.createElement('td');
	var view = document.createElement('a');

	id.appendChild(document.createTextNode(item.id));
	date.appendChild(document.createTextNode(item.date));
	name.appendChild(document.createTextNode(item.name));
	state.innerHTML = printFileState(item.state);

	view.appendChild(document.createTextNode('Consulter #' + item.id));
	view.href = '#deployment';
	view.addEventListener('click', {
		id: item.id,
		handleEvent: function(event) {
			HashNav.callbacks['deployment'](this.id);
		}
	}, true);

	line.appendChild(id);
	line.appendChild(date);
	line.appendChild(name);
	line.appendChild(state);
	line.appendChild(actions);
	actions.appendChild(view);
	
	return line;
}

$('#pause-button').addEventListener('click', function() {
	if (confirm('Etes-vous sûr de vouloir mettre en pause le serveur ?')) {
		Ajax.request('/ajax/pause_deployments', null, function(content) {
			var content = JSON.parse(content);
			if (content.state == "done") {
				notifySuccess("Les déploiements ont été mis en pause");
			} else {
				notifyError("Le serveur n'a pas pu mettre les déploiements en pause");
			}
		});
	}
});
