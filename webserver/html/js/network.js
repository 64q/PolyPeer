/*
 * Fichier JS spécifique à la page du réseau
 * Quentin Lebourgeois - 2012
 */

(function() {
	var args = pp.HashNav.vars;

	pp.Ajax('/ajax/network', null, function(content) {
		var view = $('#network-view');
		for (var i = 0; i < content.length; i++) {
			if (content[i].type == "zone") {
				createZone(view, content[i]);
			} else {
				view.appendChild(createHostLine('p', content[i]));
			}
		}
	});
	
	function createZone(parent, item) {
	
		var zone = document.createElement('div');
		
		zone.innerHTML += '<h3>Zone &laquo; ' + item.name + ' &raquo; \
			<small>Capacité : ' + item.cbbs + '/' + item.nc + '</small></h3>';
		
		var table = document.createElement('table');
		var tbody = document.createElement('tbody');
		table.className = 'table table-striped table-condensed';
		
		for (var i = 0; i < item.hosts.length; i++) {
			if (item.hosts[i].type == "zone") {
				createZone(zone, item.hosts[i]);
			} else {
				tbody.appendChild(createHostLine('tr', item.hosts[i]));
			}
		}	

		table.appendChild(tbody);
		zone.appendChild(table);
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
		view.href = '#!/host/ip/' + item.ip;
		view.className = 'btn';
		
		// Attachement des entités
		link.appendChild(view);
		line.appendChild(ip);
		line.appendChild(name);
		line.appendChild(state);
		line.appendChild(link);
	
		return line;
	}
})();
