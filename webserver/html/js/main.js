/* Fichier principal JS */

/**
 * handlers nécessaires pour des appels de données au serveur
 */
var handlers = {
	/**
	 * handler pour l'accueil
	 */
	home: function(content) {
		var contentTab = document.querySelector("#home");
		contentTab.innerHTML += "<p>Palourde</p>";
	},
	
	/**
	 * handler sur les déploiements
	 */
	deployments: function(content) {
		var content = JSON.parse(content);
		
		var contentTab = document.querySelector("#deployments>table");
		
		for (var i = 0; i < content.length; i++) {
			var line = document.createElement("tr");
			var id = document.createElement("td");
			var date = document.createElement("td");
			var name = document.createElement("td");
			var actions = document.createElement("td");
			var view = document.createElement("a");
			
			id.appendChild(document.createTextNode(content[i].id));
			date.appendChild(document.createTextNode(content[i].date));
			name.appendChild(document.createTextNode(content[i].name));
			
			view.addEventListener('click', {
       		id: content[i].id,
       		handleEvent: function(event) {
         		Ajax.request("deployment", "id=" + this.id, handlers.deployment);
         		changeTab(PolyPeer.currentTab, "#deployment");
         	}
         }, true);
      
			view.appendChild(document.createTextNode("Voir #" + content[i].id));
			view.href = "#deployment";
		
			line.appendChild(id);
			line.appendChild(date);
			line.appendChild(name);
			line.appendChild(actions);
			actions.appendChild(view);
			contentTab.appendChild(line);
		}
	},
	
	deployment: function(content) {
		var content = JSON.parse(content);
		var contentTab = document.querySelector("#deployment");
		contentTab.innerHTML = "<h1>" + content.name + "</h1>" + "<p>Configuration du déploiement #" + content.id + ".</p>";
	},
};

var PolyPeer = {
	currentTab: null,
	/**
	 * Init de l'application web
	 */
	init: function(hash) {
		// Gestion init des tabs
		var tabs = document.querySelectorAll(".tab");
		
		for each (var item in tabs) {
			item.style.display = "none";
		}
		
		var select = "#home";
		
		if (hash != "") {
			select = hash
		}
		
		var defaultTab = document.querySelector(select);
		defaultTab.style.display = "block";
		
		this.currentTab = select;
		var target = select.substring(1);
		Ajax.request(target, null, handlers[target]);
	},
	
	initLinks: function() {
		var links = document.querySelectorAll(".link");
		
		for (var i = 0; i < links.length; i++) {
			links[i].addEventListener('click', function() {
				changeTab(PolyPeer.currentTab, this.hash);
				var target = this.hash.substring(1);
				Ajax.request(target, null, handlers[target]);
			});
		}
	},
	
	initState: function() {
		Ajax.request("state", null, function(content) {
			var state = JSON.parse(content);
			document.querySelector("#state").innerHTML = "Etat: " + state.state;
		});
	},
};

function changeTab(o, n)
{
	document.querySelector(o).style.display = "none";
	PolyPeer.currentTab = n;
	document.querySelector(n).style.display = "block";
}

window.addEventListener('load', function() {
	PolyPeer.init(location.hash);
	PolyPeer.initLinks(); // Création des liens dynamiques
	PolyPeer.initState();
	
});
