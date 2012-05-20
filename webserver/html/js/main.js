/* Fichier principal JS */

function $(t) { return document.querySelector(t); }

/**
 * handlers nécessaires pour des appels de données au serveur
 */
var handlers = {
	/**
	 * handler pour l'accueil
	 */
	home: function(content) {
		$("#overview").innerHTML = createOverviewContent(JSON.parse(content));
	},
	
	/**
	 * handler sur les déploiements
	 */
	deployments: function(content) {
		var content = JSON.parse(content);
		var contentTab = $("#deployments>table");
		
		cleanElement(contentTab); // Nettoyage du tableau avant mise à jour
		
		contentTab.innerHTML = "<tr><th class=\"tiny-column\">#id</th><th class=\"tiny-column\">Date de déploiement</th><th>Nom</th><th class=\"tiny-column\">Etat</th><th class=\"tiny-column\">Action</th></tr>";
		
		for (var i = 0; i < content.length; i++) {
			contentTab.appendChild(createDeploymentLine(content[i]));
		}
	},
	
	deployment: function(content) {
		$("#deployment").innerHTML = createDeploymentView(JSON.parse(content));
	},
	
	topology: function(content) {
		var content = JSON.parse(content);
		var result = "";
		
		for each (var item in content) {
			result += "<h2>Zone \"" + item.name + "\"</h2>";
			result += "<ul>";
			
			for each (var host in item.hosts) {
				result += "<li>" + host.name + " : " + host.state + "</li>";
			}
			
			result += "</ul>";
		}
		
		$("#network").innerHTML = result;
		
	},
};

var PolyPeer = {
	/**
	 * Tab courant
	 */
	currentTab: null,
	
	/**
	 * Pages statiques ne nécessitant pas de récupération de contenu sur
	 * le serveur web.
	 */
	staticPages: ["doc", "new"],
	
	/**
	 * Init de l'application web
	 */
	init: function(hash) {
		// Gestion init des tabs
		var tabs = document.querySelectorAll(".tab");
		
		for each (var item in tabs) {
			item.style.display = "none";
		}
		
		var select;
		
		if (hash.length != 0) {
			select = hash
		} else {
			select = "#home";
		}
		
		var target = select.substring(1);
		
		$(select).style.display = "block";
		
		this.currentTab = select;
		
		if (this.staticPages.indexOf(target) == -1) {
			Ajax.request(target, null, handlers[target]);
		}
	},
	
	/**
	 * Initialise les liens Ajax
	 */
	initLinks: function() {
		var links = document.querySelectorAll(".link");
		
		for (var i = 0; i < links.length; i++) {
			links[i].addEventListener('click', function() {
				var target = this.hash.substring(1);
				changeTab(PolyPeer.currentTab, this.hash);
				// On chargement uniquement du contenu si la demande est une route dynamique
				if (PolyPeer.staticPages.indexOf(target) == -1) {
					Ajax.request(target, null, handlers[target]);
				}
			});
		}
	},
	
	/**
	 * Initialise l'état du serveur dans le header
	 */
	initState: function() {
		Ajax.request("state", null, function(content) {
			var state = JSON.parse(content);
			$("#state").innerHTML = "Etat : " + state.state;
		});
	},
};

function createDeploymentView(item)
{
	var result = "";
	
	result += "<h1>" + item.name + "</h1>";
	result += "<p>Vue détaillée du déploiement #" + item.id + "</p>";
	
	return result;
}

function createDeploymentLine(item)
{
	var line = document.createElement("tr");
	var id = document.createElement("td");
	var date = document.createElement("td");
	var name = document.createElement("td");
	var state = document.createElement("td");
	var actions = document.createElement("td");
	var view = document.createElement("a");

	id.appendChild(document.createTextNode(item.id));
	date.appendChild(document.createTextNode(item.date));
	name.appendChild(document.createTextNode(item.name));
	state.appendChild(document.createTextNode(item.state));

	view.addEventListener('click', {
		id: item.id,
		handleEvent: function(event) {
				Ajax.request("deployment", "id=" + this.id, handlers.deployment);
				changeTab(PolyPeer.currentTab, "#deployment");
			}
	}, true);

	view.appendChild(document.createTextNode("Consulter #" + item.id));
	view.href = "#deployment";

	line.appendChild(id);
	line.appendChild(date);
	line.appendChild(name);
	line.appendChild(state);
	line.appendChild(actions);
	actions.appendChild(view);
	
	return line;
}

function createOverviewContent(item)
{
	var result = "";
	
	result += "<p>Etat du serveur : " + item.state + "</p>";
	result += "<p>Nombre de déploiements : " + item.count_deployments + "</p>";
	
	return result;
}

function changeTab(o, n)
{
	$(o).style.display = "none";
	PolyPeer.currentTab = n;
	$(n).style.display = "block";
}

function cleanElement(elm)
{
	while (elm.firstChild) {
		elm.removeChild(elm.firstChild);
	}
}

window.addEventListener('load', function() {
	PolyPeer.init(location.hash);
	PolyPeer.initLinks(); // Création des liens dynamiques
	PolyPeer.initState();
	
	$("#formnew").addEventListener('submit', function(e) {
		Ajax.request("new_deployment", "name=" + $("#name").value + "&path=" + $("#path").value, function() {});
		e.preventDefault();
	});
});

/* EOF */
