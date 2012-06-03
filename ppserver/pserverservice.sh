#!/bin/bash
#
# Gestion du serveur PolyPeer en tant que service
# bash par Olivier


# Vérifier que l'utilisateur est bien root
#if (( `/usr/bin/id -u` != 0 )); then { echo "Il faut passer en root !!!"; exit; } fi

# Parametre du serveur

#Port d'écoute du serveur PolyPeer
PSERVERLISTEN=6666
#Port d'écoute des clients PolyPeer
PCLIENTDEST=5555

#Port du server WEB -> ne peut pas etre changé actuellement
# pour le modifier -> changer le define dans WebServer.hpp et recompiler le projet.
#PWEBSERVER=8889

#Repertoire racine pour le démon -> bien vérifier que les 
#config soit dans le repertoire sinon le serveur ne se lance pas
CHROOTDOS="/etc/ppserver" #`pwd`


start() {
PID=`cat ppserver.pid`
res=`ps -p $PID | grep ppserver`

if [ "$res" != "" ]; then
	echo "PolyPeer server is already running"
else
	ppserver -d -r $CHROOTDOS -s $PSERVERLISTEN -c $PCLIENTDEST #-w $PWEBSERVER
	echo "PolyPeer server start..."
	
fi
}

stop() {
PID=`cat ppserver.pid`
res=`ps -p $PID | grep ppserver`

if [ "$res" != "" ]; then
	kill -2 $PID
	echo "PolyPeer server stop..."
else
	echo "nothing to stop"
fi
}

status() {
PID=`cat ppserver.pid`
res=`ps -p $PID | grep ppserver`

if [ "$res" != "" ]; then
	echo "PolyPeer server running on PID $PID"
else
	echo "PolyPeer server is not currently running"
fi
}


case "$1" in
	'start')
		start
		;;
	'stop')
		stop
		;;
	'restart')
		stop 
		echo "wait 5 seconds"
		sleep 5
		start
		;;
	'status')
		status
		;;
	*)
		echo "Usage $0 {start|stop|restart|status}"
esac
 
exit 0
