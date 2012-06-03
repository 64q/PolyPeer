Installation du projet PolyPeer
===============================

Avant d'installer PolyPeer, veuillez vous assurer d'avoir les prérequis suivants :

* Des clients sous Windows ou Linux
* Un serveur sous Linux

Compilation
--------------

Le serveur se trouve dans le dossier ppserver/, une fois dedans, tapez simplement `make`
pour compiler les sources du projet.

Si vous désirer recompiler, il faut alors entrer `make clean` et `make mproper` si vous
souhaitez aussi supprimer l'executable.

Pour le client, même procédé, il se trouve dans le dossier ppclient/, une fois dedans, 
tapez simplement `make` pour compiler les sources du projet.

Si vous désirer recompiler, il faut alors entrer `make clean` et `make mproper` si vous
souhaitez aussi supprimer l'executable.

Si vous souhaitez installer votre serveur, tapez `make install`. Les fichiers seront copiés
dans /etc/ppserver ou /etc/ppclient et l'executable ajouté dans /usr/bin.

**Compilation du client sous Windows :** ouvrez simplement le fichier .cbp avec Code::Blocks
et lancez la compilation pour construire l'executable.

Lancement du serveur
-----------------------

Veillez tout d'abord a être positionné dans le dossier contenant le dossier html/ et le fichier passwd et les fichiers deployments.xml et topology.xml.

Vérifiez également que vous avez les droits nécessaires pour lire/écrire dans le dit dossier.

Le serveur se lance en ligne de commande, un certain nombre de paramètre est disponible :

* -s serverPort Port du serveur
* -c clientPort Port du client
* -w webserverPort Port du serveur web /!\ ATTENTION, n'est pas implémenté /!\ (cf. fichier CONFIG)
* -d lancer en démon
* -r repertoire de chdir pour le demon
* -h affichage de l'aide

Cette aide est directement intégrée dans l'executable.

Une fois le lancement effectué, vous pourrez visualiser l'état de votre serveur et le gérer
facilement en ouvrant votre navigateur web et en tappant l'adresse IP de votre serveur avec
le port approprié (par défaut 8889).

L'interface web est protégée par une authentification HTTP. Le nom d'utilisateur est 'admin' et le mot
de passe 'polypeer'.

Lancement du client
----------------------

Le client suit le même standard de lancement, une liste des paramètres est disponible :

* -p serverPort Port du serveur
* -c clientPort Port du client
* -s serverIp Adresse ip du serveur
* -d lancer en démon
* -r repertoire de chdir pour le demon
* -h Affichage de l'aide

Une fois le client lancé, vous devriez pouvoir visualiser son état sur l'interface web, si biensûr
vous avez correctement configuré votre fichier de topologie.

**Lancer le client au démarrage du système**

Pour cela, il faut éditer le fichier /etc/rc.local du système sous Linux ou ajouter un service sous windows.

Sous linux, ouvrez le fichier rc.local et copiez y ces deux lignes :

    cd /etc/ppclient
    ppclient -d # Lancez en deamon au minimum
    
Vous aurez alors un démon qui se lance au démarrage.


Plus d'informations
-------------------

De plus amples informations sont renseignées directement sur l'interface web.

Document rédigé par Quentin Lebourgeois
