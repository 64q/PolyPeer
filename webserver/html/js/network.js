/*
 * Fichier JS spécifique à la page du réseau
 * Quentin Lebourgeois - 2012
 */

function createZone(parent, item) {
	
	var zone = document.createElement('div');
	var title = document.createElement('h2');
	
	title.appendChild(document.createTextNode('Zone : ' + item.name + ' (Capacité : ' + item.cbbs + '/' + item.nc + ')'));
	
	var ul = document.createElement('ul');
	
	zone.appendChild(title);
	zone.appendChild(ul);
	
	for (var i = 0; i < item.hosts.length; i++) {
		if (item.hosts[i].type == "zone") {
			createZone(zone, item.hosts[i]);
		} else {
			ul.appendChild(createHostLine('li', item.hosts[i]));
		}
	}

	parent.appendChild(zone);
}

function createHostLine(type, item) {
	var line = document.createElement(type);
	var view = document.createElement('a');

	line.appendChild(document.createTextNode('@' + item.ip + ' ' + item.name + ' '));
	line.innerHTML += printState(item.state) + ' ';
	
	view.appendChild(document.createTextNode('[+]'));
	view.href = '#host';
	view.addEventListener('click', {
		ip: item.ip,
		handleEvent: function(event) {
			HashNav.callbacks['host'](this.ip);
		}
	});

	line.appendChild(view);
	
	return line;
}
