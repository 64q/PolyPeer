Configuration du projet PolyPeer
===============================

Une configuration du projet peut être nécessaire avant de le lancer. Voici les étapes à suivre.

Création du fichier de topologie
-----------------------------------

Un fichier de topologie est fourni avec l'executable pour vous montrer comment contruire votre réseau.

    <network>

	    <real>
		    <zone name="batiment_C" networkCapacity="100000" >
			    <zone name="C_07" networkCapacity="10000">
				    <host name="PC2" address="172.34.67.3" 
				            mac="08:00:27:a1:9e:61" networkCapacity="100"/>
			    </zone>	
		    </zone>
	    </real>
	
	    <virtual>
		    <zone name="virtual" networkCapacity="0">
			    <zone name="testZone" networkCapacity="0">
				    <zone ref="C_07"/>
			    </zone>
			    <host ref="PC2"/>
		    </zone>
	    </virtual>

    </network>

* &lt;network&gt; représente le réseau
* &lt;real&gt; représente la déclaration d'une zone physique
* &lt;zone&gt; déclare une zone
* &lt;host&gt; permet de déclarer un hote (networkCapacity est la capacité de l'entité en ko/s)

* &lt;virtual&gt; permet de déclarer une zone dite virtuelle
* &lt;host ref="host1" /&gt; permet de déclarer une référence sur un hote créé dans une zone physique (real)

Création du fichier de déploiement
-------------------------------------

Un fichier de déploiements est fourni avec l'executable pour vous montrer comment configurer la gestion
des déploiements sur le réseau.

    <deployments>
	    <file id="1" name="D1" serverPath="file/example.png" 
	            clientPath="file/example.png" chunkSize="3000" state="ready" date="0">
            <host ref="PC11" />
        </file>
    </deployments>

Attention, l'id doit être unique. Chaque déploiement est constitué de reférence sur des hotes ou des zones.


Config du webserver
--------------------------

Pour configurer le port du webserver, vous devrez changer la variable WB_PORT dans le fichier WebServer.hpp se trouvant dans le dossier du
webserver, une recompilation sera nécessaire.

Document rédigé par Quentin Lebourgeois
