/*
 * Fichier JS spécifique à un déploiement
 * Quentin Lebourgeois - 2012
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
			$('#deployment-date').text(content.date);
			$('#deployment-state').text(printFileState(content.state));
			$('#deployment-size').text(content.size);
			$('#deployment-nb-chunks').text(content.nbchunk);
			$('#deployment-chunk-size').text(content.chunksize);
			
			var result = '';
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
			
			pp.hasChanged = false;
			
			// Traitement rafraichissement live
			window.setTimeout(function() {
				updateHosts(args[0], args[1]);
			}, 1000);
		}
	});
	
	$('#delete-button').addEventListener('click', function() {
		if (confirm('Êtes-vous sûr de vouloir supprimer le déploiement ?')) {
			pp.Ajax('/ajax/delete_deployment', args[0] + '=' + args[1], function(content) {
				if (content.state == "done") {
					window.location = "#!/deployments";
					notifySuccess('Le déploiement a été supprimé avec succès.');
				} else {
					notifyError('Le déploiement n\'a pas pu être mis en pause.');
				}
			});
		}
	});
	
	$('#pause-button').addEventListener('click', function() {
		if (confirm('Êtes-vous sûr de vouloir mettre le déploiement en pause ?')) {
			pp.Ajax('/ajax/pause_deployment', args[0] + '=' + args[1], function(content) {
				if (content.state == "done") {
					notifySuccess('Le déploiement a été mis en pause avec succès.');
				} else {
					notifyError('Le déploiement n\'a pas pu être mis en pause.');
				}
			});
		}
	});
	
	$('#unpause-button').addEventListener('click', function() {
		if (confirm('Êtes-vous sûr de vouloir remettre en route le déploiement ?')) {
			pp.Ajax('/ajax/unpause_deployment', args[0] + '=' + args[1], function(content) {
				if (content.state == "done") {
					notifySuccess('Le déploiement a été mis remis en route avec succès.');
				} else {
					notifyError('Le déploiement n\'a pas pu être remis en route.');
				}
			});
		}
	});
	
	function updateHosts(type, ref) {
		// Récupération des infos du déploiement cible
		pp.Ajax('/ajax/deployment', type + '=' + ref, function(content) {
			if (!pp.hasChanged) {
				$('#deployment-state').text(printFileState(content.state));
				
				var result = '';
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
