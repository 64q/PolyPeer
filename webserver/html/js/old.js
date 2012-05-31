/**
 * Gestion de la navigation par hash
 */
var HashNav = {
	
	current: null,
	vars: null,
	
	/**
	 * Initialise la navigation par hash, notamment l'activation des liens spéciaux
	 */
	init: function() {
		this.evaluate();
	},
	
	/**
	 * Active les liens hash de la page
	 */
	activate: function(trg) {
		var links = qsa(trg + ' .link');
		
		for (var i = 0; i < links.length; i++) {
			// Définition du callback de click
			links[i].addEventListener('click', function() {
				var target = getTargetFromHash(this.hash);
				HashNav.callbacks[target]();
				HashNav.current = target;
			});
		}
	},
	
	/**
	 * Evalue un lien hashé
	 */
	evaluate: function() {
		// Traitement du hash composé
		vars = location.hash.split('/');
		
		// Init du tab courant (pour reprise)
		if (location.hash.length > 0) {
			this.current = getTargetFromHash(vars[0]);
		} else {
			this.current = "home";
		}
		
		vars.shift();
		
		if (HashNav.callbacks[this.current] != undefined) {
			HashNav.callbacks[this.current](vars);
		}
	},
	
	/**
	 * Callbacks sur les adresses
	 */
	callbacks: {
	
		/**
		 * Effectue des actions pour afficher l'onglet #home
		 */
		home: function() {
			callPage('#home', null, function() {
				// Récupération des informations dynamiques
				Ajax.request('/ajax/get_stats', null, function(content) {
					var content = JSON.parse(content);
					var result = '<dl>';
					result += '<dt>Etat du serveur</dt><dd>L\'état du serveur est ' + printServerState(content.state) + '</dd>';
					result += '<dt>Nombre de déploiements en cours</dt><dd>Il y a actuellement ' + content.count_deployments + ' en cours</dd>';
					result += '<dt>Nombre d\'entitées sur le réseau</dt><dd>Il y a ' + content.count_hosts + ' hotes sur le réseau</dd>';
					result += '</dl>';
				
					$('#overview').innerHTML = result;
				});
			});
		},
		
		/**
		 * Affichage de l'onglet #deployements
		 */
		deployments: function() {
			callPage('#deployments', null, function() {
				// Récupération des déploiements sur le serveur
				Ajax.request('/ajax/deployments', null, function(content) {
					var content = JSON.parse(content);
					loadScript('js/deployments.js', function() {
						var contentTab = $("#deployments>table");
						for (var i = 0; i < content.length; i++) {
							contentTab.appendChild(createDeploymentLine(content[i]));
						}
					});
				});
			});
		},
		
		/**
		 * Affichage de l'onglet #deployment
		 */
		deployment: function(id) {
			if (id[1] == undefined) {
				$('#content').innerHTML = '<h1>Page introuvable</h1><p class="alert alert-error">La page demandée est introuvable.</p>';
				return;
			}
			
			callPage('#deployment', null, function() {		
				// Récupération des infos du déploiement cible
				Ajax.request('/ajax/deployment', 'id=' + id[1], function(content) {
					var content = JSON.parse(content);
					var result;
					
					if (content.state == 'error') {
						result = notifyError('Impossible de récupérer le déploiement');
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
					}
					
					$('#deployment').innerHTML = result;
					$('#refresh-button').addEventListener('click', function() {
						HashNav.callbacks.deployment(id[1]);
					});
				});
			});
		},
		
		/**
		 * Affichage de l'onglet #network
		 */
		network: function() {
			callPage('#network', null, function() {
				Ajax.request('/ajax/network', null, function(content) {
					var content = JSON.parse(content);
					loadScript('js/network.js', function() {
						var view = $('#network-view');
						for (var i = 0; i < content.length; i++) {
							if (content[i].type == "zone") {
								createZone(view, content[i]);
							} else {
								view.appendChild(createHostLine('p', content[i]));
							}
						}
					});
				});
			});
		},
		
		/**
		 * Affichage de l'onglet #new
		 */
		new: function() {
			callPage('#new', null, function() {
				loadScript('js/new.js');
			});
		},
		
		/**
		 * Affichage de l'onglet #host
		 */
		host: function(ip) {
			if (ip[1] == undefined) {
				$('#content').innerHTML = '<h1>Page introuvable</h1><p class="alert alert-error">La page demandée est introuvable.</p>';
				return;
			}
			
			callPage('#host', null, function() {
				Ajax.request('/ajax/get_host', 'ip=' + ip[1], function(content) {
					var content = JSON.parse(content);
					var result = '<table class="table table-striped">';
				
					for (var i = 0; i < content.deployments.length; i++) {
						var width = (content.deployments[i].current / content.deployments[i].total) * 100;
						result += '<tr><td>' + content.deployments[i].name + '</td><td>' + printDeployState(content.deployments[i].state) + '</td>\
						<td class="large-column"><div class="progress progress-striped active"> \
    								<div class="bar" style="width: ' + width + '%;"></div></div></td><td><span>' + content.deployments[i].current + '/' + content.deployments[i].total + '</span></td></tr>';
					}
				
					$('#host-info').innerHTML = '<ul><li><strong>Nom : </strong>' + content.name + '</li><li><strong>IP : </strong>' + content.ip + '</li><li><strong>Etat : </strong>' + printHostState(content.state) + '</li></ul>';
					$('#host-deployments').innerHTML = result;
					$('#refresh-button').addEventListener('click', function() {
						HashNav.callbacks.host(ip[1]);
					});
				});
			});
		},
		
		/**
		 * Effectue des actions pour afficher l'onglet #doc
		 */
		doc: function() {
			callPage('#doc', null, function() {});
		},
	},
};
