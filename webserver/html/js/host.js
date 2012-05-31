/*
 * Fichier spécifique à la visualisation d'un host
 * Quentin Lebourgeois - 2012
 */

(function(){
	var args = pp.HashNav.vars;

	if (args.length < 2) {
		pp.Utils.error('404'); return;
	}
	
	pp.Ajax('/ajax/get_host', args[0] + '=' + args[1], 
		function(content) {
			var result = '';

			for (var i = 0; i < content.deployments.length; i++) {
				var width = (content.deployments[i].current / content.deployments[i].total) * 100;
				result += '<tr><td>' + content.deployments[i].name + '</td><td>' + printDeployState(content.deployments[i].state) + '</td>\
				<td class="large-column"><div class="progress"> \
							<div class="bar" style="width: ' + width + '%;"></div></div></td><td><span>' + content.deployments[i].current + '/' + content.deployments[i].total + '</span></td></tr>';
			}

			$('#host-header').text(content.name);
			$('#host-ip').text(content.ip);
			$('#host-name').text(content.name);
			$('#host-state').text(printHostState(content.state));
			$('#host-deployments').text(result);
			
			pp.hasChanged = false;
			
			// Lancement rafraichissement live
			window.setTimeout(function() {
				updateHostDeployments(args[0], args[1]);
			}, 1000);
		},
		function() {
			pp.Utils.error('404');
		}
	);
	
	function updateHostDeployments(type, ref) {
		if (!pp.hasChanged) {
			pp.Ajax('/ajax/get_host', type + '=' + ref, function(content) {
				var result = '';

				for (var i = 0; i < content.deployments.length; i++) {
					var width = (content.deployments[i].current / content.deployments[i].total) * 100;
					result += '<tr><td>' + content.deployments[i].name + '</td><td>' + printDeployState(content.deployments[i].state) + '</td>\
					<td class="large-column"><div class="progress"> \
								<div class="bar" style="width: ' + width + '%;"></div></div></td><td><span>' + content.deployments[i].current + '/' + content.deployments[i].total + '</span></td></tr>';
				}
			
				$('#host-deployments').text(result);
			});
		
			window.setTimeout(function() {
				updateHostDeployments(type, ref);
			}, 1000);
		} else {
			pp.hasChanged = false;
		}
	}
})();
