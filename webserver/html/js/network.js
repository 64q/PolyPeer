/*
 * Fichier JS spécifique à la page du réseau
 * Quentin Lebourgeois - 2012
 */

function createZone(item) {
	
	var zone = document.createElement('div');
	var title = document.createElement('h2');
	
	title.appendChild(document.createTextNode("Zone : " + item.name));
	
	var ul = document.createElement('ul');
	
	for (var i = 0; i < item.hosts.length; i++) {
		if (item.hosts[i].type == "zone") {
			createZone(item.hosts[i]);
		} else {
			ul.appendChild(createHostLine(item.hosts[i]));
		}
	}
	
	zone.appendChild(title);
	zone.appendChild(ul);
	
	return zone;
}

function createHostLine(item) {
	var line = document.createElement('li');
	var view = document.createElement('a');

	line.appendChild(document.createTextNode('@' + item.ip + ' ' + item.name + ' '));

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
