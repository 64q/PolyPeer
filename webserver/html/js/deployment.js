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
		$('#deployment-name').text(content.name);
		
		if (content.state == 'error') {
			notifyError('Impossible de récupérer le déploiement');
		} else {
			$('#deployment-filename').text(content.filename);
			$('#deployment-state').text(printFileState(content.state));
			$('#deployment-size').text(content.size);
			$('#deployment-nb-chunks').text(content.nbchunk);
			$('#deployment-chunk-size').text(content.chunksize);
			
			var result;
			for (var i = 0; i < content.hosts.length; i++) {
				var width = (content.hosts[i].current / content.hosts[i].total) * 100;
				var tmp_state;
				
				if (content.hosts[i].host_state == "offline") {
					tmp_state = printHostState("offline");
				} else {
					tmp_state = printDeployState(content.hosts[i].state);
				}
				
				result += '<tr><td>' + content.hosts[i].ip + '</td><td>' + content.hosts[i].name + '</td><td>' + tmp_state + '</td><td class="large-column">\
					<div class="progress progress-striped active"> \
						<div class="bar" style="width: ' + width + '%;"></div></div></td><td><span style="float: left;margin-right: 5px;">' + content.hosts[i].current + '/' + content.hosts[i].total + '</span></td></tr>';
			}
			
			$('#deployment-hosts').text(result);
			
			pp.hasChanged = false;
			
			// Traitement rafraichissement live
			window.setTimeout(function() {
				updateHosts(args[0], args[1]);
			}, 1000);
		}
	});
	
	function updateHosts(type, ref) {
		// Récupération des infos du déploiement cible
		pp.Ajax('/ajax/deployment', type + '=' + ref, function(content) {
			if (!pp.hasChanged) {
				var result;
				for (var i = 0; i < content.hosts.length; i++) {
					var width = (content.hosts[i].current / content.hosts[i].total) * 100;
					var tmp_state;
		
					if (content.hosts[i].host_state == "offline") {
						tmp_state = printHostState("offline");
					} else {
						tmp_state = printDeployState(content.hosts[i].state);
					}
		
					result += '<tr><td>' + content.hosts[i].ip + '</td><td>' + content.hosts[i].name + '</td><td>' + tmp_state + '</td><td class="large-column">\
						<div class="progress"> \
							<div class="bar" style="width: ' + width + '%;"></div></div></td><td><span style="float: left;margin-right: 5px;">' + content.hosts[i].current + '/' + content.hosts[i].total + '</span></td></tr>';
				}
	
				$('#deployment-hosts').text(result);		
		
				window.setTimeout(function() {
					updateHosts(type, ref);
				}, 1000);
			} else {
				pp.hasChanged = false;
			}
		});
	}
})();
