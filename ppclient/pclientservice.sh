#!/bin/bash
#
# Gestion du client PolyPeer en tant que service unix
# bash par Olivier


# Vérifier que l'utilisateur est bien root
#if (( `/usr/bin/id -u` != 0 )); then { echo "Il faut passer en root !!!"; exit; } fi

# Parametre du serveur

#Port d'écoute du client PolyPeer
PCLIENTLISTEN=5555
#Port d'écoute du server PolyPeer
PSERVERDEST=6666
#Port d'écoute du server PolyPeer
ADDRSERVER="192.168.0.14"
#Repertoire racine pour le démon
CHROOTDOS="/etc/ppclient"



start() {
PID=`cat ppclient.pid`
res=`ps -p $PID | grep ppclient`

if [ "$res" != "" ]; then
	echo "PolyPeer client is already running"
else
	ppclient -d -r $CHROOTDOS -c $PCLIENTLISTEN -p $PSERVERDEST  -s $ADDRSERVER
	echo "PolyPeer client start..."
fi

}

stop() {
PID=`cat ppclient.pid`
res=`ps -p $PID | grep ppclient`

if [ "$res" != "" ]; then
	kill -2 $PID
	kill -9 $PID
	echo "PolyPeer client stop..."
else
	echo "nothing to stop"
fi
}

status() {
PID=`cat ppclient.pid`
res=`ps -p $PID | grep ppclient`

if [ "$res" != "" ]; then
	echo "PolyPeer client running on PID $PID"
else
	echo "PolyPeer client is not currently running"
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
