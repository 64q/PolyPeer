/*
 * Utilitaires JS - Quentin Lebourgeois 2012
 */

/**
 * Raccourcissement de la fonction querySelector
 */
function $(t) { 
	return document.querySelector(t); 
}

/**
 * Wrapper de querySelectorAll
 */
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
	request: function(target, params, callback, fail) {
		var xhr = this.getXMLHttpRequest();

		xhr.onreadystatechange = function() {
			if (xhr.readyState == 4 && (xhr.status == 200 || xhr.status == 0)) {
				if (xhr.responseText == "") {
					fail();
				} else {
					callback(xhr.responseText);
				}
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
					result += '<li><strong>Etat du serveur : </strong>' + printServerState(content.state) + '</li>';
					result += '<li><strong>Nombre de déploiements en cours : </strong>' + content.count_deployments + '</li>';
					result += '<li><strong>Nombre d\'entitées sur le réseau : </strong>' + content.count_hosts + '</li>';
					result += '</ul>';
				
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
						result += '<li><strong>Fichier : </strong>' + content.filename + '</li>';
						result += '<li><strong>Etat : </strong>' + content.state + '</li>';
						result += '<li><strong>Taille : </strong>' + content.size + ' o</li>';
						result += '<li><strong>Nombre de chunks : </strong>' + content.nbchunk + '</li>';
						result += '<li><strong>Taille d\'un chunk : </strong>' + content.chunksize + ' o</li>';
						result += '</ul>';
					
						result += '<h2>Hotes incluses</h2>';
						result += '<table>';
						
						for (var i = 0; i < content.hosts.length; i++) {
							result += '<tr><td>' + content.hosts[i].ip + '</td><td>' + content.hosts[i].name + '</td><td>' + printDeployState(content.hosts[i].state) + '</td><td>' + content.hosts[i].current + '/' + content.hosts[i].total + '</td></tr>';
						}
					
						result += '</ul>';
					}
					
					$('#deployment').innerHTML = result;
					$('#refresh-button').addEventListener('click', function() {
						HashNav.callbacks.deployment(id);
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
			callPage('#host', null, function() {
				Ajax.request('/ajax/get_host', 'ip=' + ip, function(content) {
					var content = JSON.parse(content);
					var result = '<ul>';
				
					for (var i = 0; i < content.deployments.length; i++) {
						result += '<li>' + content.deployments[i].name + ' [' + printDeployState(content.deployments[i].state) + '] (' + content.deployments[i].current + '/' + content.deployments[i].total + ')</li>';
					}
				
					$('#host-info').innerHTML = '<ul><li><strong>Nom : </strong>' + content.name + '</li><li><strong>IP : </strong>' + content.ip + '</li><li><strong>Etat : </strong>' + printHostState(content.state) + '</li></ul>';
					$('#host-deployments').innerHTML = result;
					$('#refresh-button').addEventListener('click', function() {
						HashNav.callbacks.host(ip);
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
		if (PolyPeer.stats.state == "offline") {
			$('#content').innerHTML = '<h1>Erreur du serveur</h1><p>Le serveur web ne répond pas !</p>';
		} else {
			$('#content').innerHTML = content;
			HashNav.activate('#content'); // Important, après un chargement, il faut activer les hash links
			callback();
		}
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

/**
 * Affichage d'un succès
 */
function notifySuccess(msg) {
	$('#notifs').innerHTML = '<p class="success">' + msg + '</p>';
}

/**
 * Affichage d'une erreur
 */
function notifyError(msg) {
	$('#notifs').innerHTML = '<p class="error">' + msg + '</p>';
}

/**
 * Affichage host state formaté
 */
function printHostState(state)
{
	var result;
	
	switch (state)
	{
		case 'download':
			result = '<span class="status download">En téléchargement</span>';
			break;
		case 'wait':
			result = '<span class="status wait">En attente</span>';
			break;
		case 'offline':
			result = '<span class="status offline">Hors ligne</span>';
			break;
		default:
			result = '<span class="status undefined">Non défini</span>';
	}
	
	return result;
}

/**
 * Affichage deployment state formaté
 */
function printDeployState(state)
{
	var result;
	
	switch (state)
	{
		case 'wait':
			result = '<span class="status wait">En attente</span>';
			break;
		case 'finished':
			result = '<span class="status finished">Fini</span>';
			break;
		case 'init':
			result = '<span class="status init">Initialisation</span>';
			break;
		case 'disk full':
			result = '<span class="status full">Disque plein</span>';
			break;
		default:
			result = '<span class="status undefined">Non défini</span>';
	}
	
	return result;
}

/**
 * Affichage file state formaté
 */
function printFileState(state)
{
	var result;
	
	switch (state)
	{
		case 'ready':
			result = '<span class="status ready">Prêt</span>';
			break;
		case 'deployment':
			result = '<span class="status deploy">En déploiement</span>';
			break;
		case 'finished':
			result = '<span class="status finished">Fini</span>';
			break;
		case 'error':
			result = '<span class="status err">En erreur</span>';
			break;
		case 'pause':
			result = '<span class="status pause">En pause</span>';
			break;
		default:
			result = '<span class="status undefined">Non défini</span>';
	}
	
	return '<span class="status">' + result + '</span>';
}

function printServerState(state)
{
	var result;
	
	if (state == "online") {
		result = '<span class="server-state online">En ligne</span>';
	} else {
		result ='<span class="server-state offline">Hors ligne</span>';
	}
	
	return result;
}
