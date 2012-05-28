/*
 * Utilitaires JS - Quentin Lebourgeois 2012
 */

/**
 * Raccourcissement de la fonction querySelector
 */
function $(t) { 
	return document.querySelector(t); 
}

function qsa(t) {
	return document.querySelectorAll(t);
}

var Ajax = {
	/**
	 * Fonction d'appel AJAX
	 * @param file
	 * 	fichier à appeler
	 * @param params
	 * 	paramètres à envoyer
	 * @param callback
	 * 	fonction executée à la fin de l'appel
	 */
	request: function(target, params, callback) {
		var xhr = this.getXMLHttpRequest();

		xhr.onreadystatechange = function() {
			if (xhr.readyState == 4 && (xhr.status == 200 || xhr.status == 0)) {
				callback(xhr.responseText);
			}
		};
		
		if (params != undefined) {
			xhr.open('GET', target + '?' + params, true);
		} else {
			xhr.open('GET', target, true);
		}
		xhr.send(null);
	},

	/**
	 * Fonction XMLHttpRequest
	 * @return xhr
	 */
	getXMLHttpRequest: function() {
		var xhr = null;

		if (window.XMLHttpRequest || window.ActiveXObject) {
			if (window.ActiveXObject) {
				try {
					xhr = new ActiveXObject("Msxml2.XMLHTTP");
				} catch(e) {
					xhr = new ActiveXObject("Microsoft.XMLHTTP");
				}
			} else {
				xhr = new XMLHttpRequest(); 
			}
		} else {
			alert("Votre navigateur ne supporte pas l'objet XMLHTTPRequest...");
			return null;
		}

		return xhr;
	}
};

/**
 * Gestion de la navigation par hash
 */
var HashNav = {
	
	current: null,
	
	/**
	 * Initialise la navigation par hash, notamment l'activation des liens spéciaux
	 */
	init: function() {
		this.activate('body');
		
		// Init du tab courant (pour reprise)
		if (location.hash.length > 0) {
			this.current = getTargetFromHash(location.hash);
		} else {
			this.current = "home";
		}
		
		HashNav.callbacks[this.current]();
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
					var result = '<ul>';
					result += '<li><strong>Etat du serveur : </strong>' + printState(content.state) + '</li>';
					result += '<li><strong>Nombre de déploiements en cours : </strong>' + content.count_deployments + '</li>';
					result += '<li><strong>Nombre d\'entitées sur le réseau : </strong>' + content.count_hosts + '</li>';
					result += '</ul>';
				
					$('#overview').innerHTML = result;
				});
			});
		},
		
		admin: function() {
			callPage('#admin', null, function() { 
				loadScript('js/admin.js');
			});
		},
		
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
		
		deployment: function(id) {
			callPage('#deployment', null, function() {		
				// Récupération des infos du déploiement cible
				Ajax.request('/ajax/deployment', 'id=' + id, function(content) {
					var content = JSON.parse(content);
					var result;
					
					if (content.state == 'error') {
						result = notifyError('Impossible de récupérer le déploiement');
					} else {
						result = '<h1>' + content.name + '</h1>';
						result += '<ul>';
						result += '<li>Etat : ' + content.state + '</li>';
						result += '<li>Taille : ' + content.size + ' o</li>';
						result += '<li>Nombre de chunks : ' + content.nbchunk + '</li>';
						result += '<li>Taille d\'un chunk : ' + content.chunksize + ' o</li>';
						result += '</ul>';
					
						result += '<h2>Hotes incluses</h2>';
						result += '<ul>';
					
						for (var i = 0; i < content.hosts.length; i++) {
							result += '<li>@' + content.hosts[i].ip + ' ' + content.hosts[i].name + ' [' + content.hosts[i].state + '] (' + content.hosts[i].current + '/' + content.hosts[i].total + ')</li>';
						}
					
						result += '</ul>';
					}
					
					$('#deployment').innerHTML = result;
				});
			});
		},
		
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
		
		new: function() {
			callPage('#new', null, function() {
				loadScript('js/new.js');
			});
		},
		
		host: function(ip) {
			callPage('#host', null, function() {
				Ajax.request('/ajax/get_host', 'ip=' + ip, function(content) {
					var content = JSON.parse(content);
					var result = '<ul>';
				
					for (var i = 0; i < content.deployments.length; i++) {
						result += '<li>' + content.deployments[i].name + ' [' + content.deployments[i].state + '] (' + content.deployments[i].current + '/' + content.deployments[i].total + ')</li>';
					}
				
					$('#host-info').innerHTML = '<ul><li><strong>Nom : </strong>' + content.name + '</li><li><strong>IP : </strong>' + content.ip + '</li><li><strong>Etat : </strong>' + printState(content.state) + '</li></ul>';
					$('#host-deployments').innerHTML = result;
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

/**
 * Retourne la cible d'un lien "hashé"
 */
function getTargetFromHash(hash) {
	return hash.substring(1);
}

/**
 * Appelle la ressource sur le serveur
 */
function callPage(tab, args, callback) {
	Ajax.request('/pages/' + getTargetFromHash(tab) + '.html', args, function(content) {
		$('#content').innerHTML = content;
		HashNav.activate('#content'); // Important, après un chargement, il faut activer les hash links
		callback();
	});
}

/**
 * Charge un script JS dynamiquement
 */
function loadScript(target, callback) {
	var scriptElement = document.createElement('script');
   scriptElement.src = target;
   document.body.appendChild(scriptElement);
   
   scriptElement.onload = callback;
}

function notifySuccess(msg) {
	$('#notifs').innerHTML = '<p class="success">' + msg + '</p>';
}

function notifyError(msg) {
	$('#notifs').innerHTML = '<p class="error">' + msg + '</p>';
}

function printState(state) {
	if (state == 'offline') {
		return '<span class="error">Hors-ligne</span>';
	} else if (state == 'online') {
		return '<span class="success">En ligne</span>';
	} else if (state == 'download') {
		return '<span class="info">Download</span>';
	} else {
		return state;
	}
}
