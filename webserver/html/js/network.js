/*
 * Fichier JS spécifique à la page du réseau
 * Quentin Lebourgeois - 2012
 */

function createZone(parent, item) {
	
	var zone = document.createElement('table');
	zone.innerHTML = '<tr><th colspan="4">Zone &laquo; ' + item.name + ' &raquo; \
		(Capacité : ' + item.cbbs + '/' + item.nc + ')'; 
	
	for (var i = 0; i < item.hosts.length; i++) {
		if (item.hosts[i].type == "zone") {
			createZone(zone, item.hosts[i]);
		} else {
			zone.appendChild(createHostLine('tr', item.hosts[i]));
		}
	}

	parent.appendChild(zone);
}

function createHostLine(type, item) {
	var line = document.createElement(type);
	var ip = document.createElement('td');
	var name = document.createElement('td');
	var state = document.createElement('td');
	var link = document.createElement('td');
	var view = document.createElement('a');
	
	ip.appendChild(document.createTextNode(item.ip));
	name.appendChild(document.createTextNode(item.name));
	state.innerHTML = printHostState(item.state);
	
	// Configuration du lien dynamique
	view.appendChild(document.createTextNode('Détails'));
	view.href = '#host';
	view.addEventListener('click', {
		ip: item.ip,
		handleEvent: function(event) {
			HashNav.callbacks['host'](this.ip);
		}
	});

	// Attachement des entités
	link.appendChild(view);
	line.appendChild(ip);
	line.appendChild(name);
	line.appendChild(state);
	line.appendChild(link);
	
	return line;
}
