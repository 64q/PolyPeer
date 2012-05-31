/*
 * Fichier JS spécifique à un déploiement
 */

(function() {
	var args = pp.HashNav.vars;
	
	if (args.length < 2) {
		pp.Utils.error('404'); return;
	}
	
	// Récupération des infos du déploiement cible
	pp.Ajax('/ajax/deployment', args[0] + '=' + args[1], function(content) {
		var result;
	
		if (content.state == 'error') {
			notifyError('Impossible de récupérer le déploiement');
		} else {
			result = '<div class="page-header"><h1>' + content.name + '</h1></div>';
			result += '<ul>';
			result += '<li><strong>Fichier : </strong>' + content.filename + '</li>';
			result += '<li><strong>Etat : </strong>' + printFileState(content.state) + '</li>';
			result += '<li><strong>Taille : </strong>' + content.size + ' o</li>';
			result += '<li><strong>Nombre de chunks : </strong>' + content.nbchunk + '</li>';
			result += '<li><strong>Taille d\'un chunk : </strong>' + content.chunksize + ' o</li>';
			result += '</ul>';
			result += '<h3>Actions</h3>';
			result += '<p><button class="btn btn-warning" id="pause-button">Pause</button>&nbsp; \
				<button class="btn btn-danger" id="delete-button">Supprimer</button></p>';
			result += '<h3>Hotes incluses</h3>';
			result += '<table class="table table-striped">';
		
			for (var i = 0; i < content.hosts.length; i++) {
				var width = (content.hosts[i].current / content.hosts[i].total) * 100;
				result += '<tr><td>' + content.hosts[i].ip + '</td><td>' + content.hosts[i].name + '</td><td>' + printDeployState(content.hosts[i].state) + '</td><td class="large-column">\
					<div class="progress progress-striped active"> \
						<div class="bar" style="width: ' + width + '%;"></div></div></td><td><span style="float: left;margin-right: 5px;">' + content.hosts[i].current + '/' + content.hosts[i].total + '</span></td></tr>';
			}
	
			result += '</ul>';
			
			$('#deployment').text(result);
		}
	});
})();
