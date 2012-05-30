/*
 * Fichier spécifique à l'host
 */

(function(){
	var args = pp.HashNav.vars;

	if (args.length < 2) {
		pp.Utils.error('404'); return;
	}
	
	pp.Ajax('/ajax/get_host', args[0] + '=' + args[1], 
		function(content) {
			var result = '<table class="table table-striped">';

			for (var i = 0; i < content.deployments.length; i++) {
				var width = (content.deployments[i].current / content.deployments[i].total) * 100;
				result += '<tr><td>' + content.deployments[i].name + '</td><td>' + printDeployState(content.deployments[i].state) + '</td>\
				<td class="large-column"><div class="progress progress-striped active"> \
							<div class="bar" style="width: ' + width + '%;"></div></div></td><td><span>' + content.deployments[i].current + '/' + content.deployments[i].total + '</span></td></tr>';
			}

			$('#host-info').text('<ul><li><strong>Nom : </strong>' + content.name + '</li><li><strong>IP : </strong>' + content.ip + '</li><li><strong>Etat : </strong>' + printHostState(content.state) + '</li></ul>');
			$('#host-deployments').text(result);
		},
		function() {
			pp.Utils.error('404');
		}
	);
})();
