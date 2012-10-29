# Makefile de céation du serveur polypeer
#
# Auteur: Equipe de dev
# Date: lun. 21 mai 2012 18:48:11 CEST 
# Version: 
#
# Actions :
#	make all 		: compilation (defaut)
#	make clean 		: suppression des .o
#	make mrproper 	: suppression des .o et de l'exe



# Liste des dossiers à lier
FM =../filemanager/
PACKET =../packet/
CONNECT =../connection/
TCP =../tcp/
XML=../datamanager/
TinyXML=../datamanager/include/tinyxml/
LOG=../logger/
DATA=../data/
CB=../callback/
TCPEXCEPT=../tcp/include/Exceptions/
WEB=../webserver/
BASESERVER=../baseserver/
ALGO=../algorithm/
MUTEX=../mutex/

# Variables de nomage et de localisation
CC=g++
EXEC=ppserver
SRC=src/
INC=include/

# Flag pour le linker
LDFLAGS=-lpthread -pthread -ldl -g -lrt
# Flag préprocessing et compilation
CFLAGS=-Wall -I$(INC) -I$(FM)$(INC) -I$(PACKET)$(INC) -I$(MUTEX)$(INC) -I$(DATA)$(INC) -I$(CB)$(INC) -I$(CONNECT)$(INC) -I$(ALGO)$(INC) -I$(TCP)$(INC) -I$(LOG)$(INC) -I$(XML)$(INC) -I$(WEB)$(INC) -I$(TCPEXCEPT) -I$(TinyXML) -I$(BASESERVER)$(INC) -D TIXML_USE_STL


# commande par defaut
all: $(EXEC)


############################
#
#          MAIN
#
############################

# Compilation du main
main.o: $(SRC)main.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)


############################
#
#     SERVEUR PolyPeer
#
############################

# Compilation du serveur PolyPeer
PolypeerServer.o: $(SRC)PolypeerServer.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

############################
#
#     SERVEUR de base
#
############################

BaseServ=BaseServer.o

# Compilation du serveur PolyPeer
BaseServer.o: $(BASESERVER)$(SRC)BaseServer.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

############################
#
#       WEB SERVEUR
#
############################

WebServ=routes.o WebServer.o mongoose.o

# Compilation des routes
routes.o: $(WEB)$(SRC)routes.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation du server
WebServer.o: $(WEB)$(SRC)WebServer.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)
	
# Compilation de mongoose
mongoose.o: $(WEB)$(SRC)mongoose.c
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

############################
#
#   STRUCTURE PRINCIPALE
#
############################

MainStruct=Zone.o Host.o Entity.o File.o DeploymentState.o XMLTool.o ServerData.o State.o

# Compilation de Zone
Zone.o: $(XML)$(SRC)Zone.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation de Host
Host.o: $(XML)$(SRC)Host.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation de Entity
Entity.o: $(XML)$(SRC)Entity.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation de File
File.o: $(XML)$(SRC)File.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation de DeploymentState
DeploymentState.o: $(XML)$(SRC)DeploymentState.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)
	
# Compilation de XMLTool
XMLTool.o: $(XML)$(SRC)XMLTool.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)
	
# Compilation de ServerData
ServerData.o: $(XML)$(SRC)ServerData.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

State.o: $(XML)$(SRC)State.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)


############################
#
#    LIBRAIRY TINY XML
#
############################

LibXML=tinyxml.o tinyxmlparser.o tinyxmlerror.o tinystr.o
	
# Compilation de tinyxml
tinyxml.o: $(TinyXML)tinyxml.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation de tinyxmlparser
tinyxmlparser.o: $(TinyXML)tinyxmlparser.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation de tinyxmlerror
tinyxmlerror.o: $(TinyXML)tinyxmlerror.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation de tinystr
tinystr.o: $(TinyXML)tinystr.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)
	

############################
#
#       FILEMANAGER
#
############################

FileManager=FileManager.o Chunk.o

# Compilation du Chunk
Chunk.o: $(FM)$(SRC)Chunk.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation du FileManager
FileManager.o: $(FM)$(SRC)FileManager.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)


############################
#
#     PACKET::PROTOCOL
#
############################

PacketManager= Packet.o PacketReady.o PacketDiskFull.o PacketSendOperationFinished.o PacketMd5Error.o PacketSendChunk.o PacketSendOperation.o PacketChunkReceived.o PacketNewFile.o PacketAddHost.o PacketRemoveHost.o

# Compilation du Packet
Packet.o: $(PACKET)$(SRC)Packet.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)
	
# Compilation du PacketReady
PacketReady.o: $(PACKET)$(SRC)PacketReady.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation du PacketDiskFull
PacketDiskFull.o: $(PACKET)$(SRC)PacketDiskFull.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation du PacketSendOperationFinished
PacketSendOperationFinished.o: $(PACKET)$(SRC)PacketSendOperationFinished.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)
	
# Compilation du PacketMd5Error
PacketMd5Error.o: $(PACKET)$(SRC)PacketMd5Error.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)
	
# Compilation du PacketSendChunk
PacketSendChunk.o: $(PACKET)$(SRC)PacketSendChunk.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)
	
# Compilation du PacketSendOperation
PacketSendOperation.o: $(PACKET)$(SRC)PacketSendOperation.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation du PacketChunkReceived
PacketChunkReceived.o: $(PACKET)$(SRC)PacketChunkReceived.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation du PacketNewFile
PacketNewFile.o: $(PACKET)$(SRC)PacketNewFile.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation du PacketNewFile
PacketAddHost.o: $(PACKET)$(SRC)PacketAddHost.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation du PacketReady
PacketRemoveHost.o: $(PACKET)$(SRC)PacketRemoveHost.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

############################
#
#      CALLBACK MANAGER
#
############################

CallbackManager=PacketCallback.o callbackFunctionServer.o

# Compilation du PacketManager
PacketCallback.o:  $(CB)$(SRC)PacketCallback.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation du callbackFunctionServer
callbackFunctionServer.o: $(CB)$(SRC)callbackFunctionServer.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)


############################
#
#   DEPLOYMENT ALGORITHM
#
############################

Algorithm=ShareDeployment.o DeploymentAlgorithm.o

# Compilation du DeploymentAlgorithm
DeploymentAlgorithm.o:  $(ALGO)$(SRC)DeploymentAlgorithm.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation du ShareDeployment
ShareDeployment.o:  $(ALGO)$(SRC)ShareDeployment.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)


############################
#
#     	    DATA
#
############################

Data=Data.o

# Compilation de Data
Data.o: $(DATA)$(SRC)Data.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

############################
#
#    CONNECTION MANAGER
#
############################

ConnectionManager=ConnectionManager.o Connection.o BaseSocket.o ServerSocket.o Socket.o


# Compilation du ConnectionManager
ConnectionManager.o: $(CONNECT)$(SRC)ConnectionManager.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation de Connection
Connection.o: $(CONNECT)$(SRC)Connection.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation du BaseSocket
BaseSocket.o: $(TCP)$(SRC)BaseSocket.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation du ServerSocket
ServerSocket.o: $(TCP)$(SRC)ServerSocket.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation du Socket
Socket.o: $(TCP)$(SRC)Socket.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)


############################
#
#      LOGGER
#
############################

Logger=Logger.o

# Compilation du Logger
Logger.o:  $(LOG)$(SRC)Logger.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

############################
#
#      MUTEX
#
############################

Mutex=Mutex.o Semaphore.o

# Compilation de l'enveloppe mutex
Mutex.o:  $(MUTEX)$(SRC)Mutex.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation de l'enveloppe semaphore
Semaphore.o:  $(MUTEX)$(SRC)Semaphore.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)


############################
#
#    EDITION DES LIENS
#    CREATION DE L'EXE
#
############################


$(EXEC): main.o PolypeerServer.o $(BaseServ) $(MainStruct) $(LibXML) $(Mutex) $(FileManager) $(PacketManager) $(CallbackManager) $(Data) $(ConnectionManager)  $(Algorithm) $(Logger) $(WebServ)
	@echo "Link output files..."
	@$(CC) -o $@  $^ $(LDFLAGS)
	@echo "OK"
	@echo "Program name is $(EXEC)"

############################
#
#    INSTALLATION
#
############################

install: all
	cp $(EXEC) /usr/bin
	cp pserverservice.sh /etc/init.d/
	mkdir /etc/ppserver
	cp deployments.xml /etc/ppserver
	cp topology.xml /etc/ppserver
	cp -r html /etc/ppserver
	cp passwd /etc/ppserver
	@echo "Programme installé avec succès (voir /etc/ppserver pour les fichiers de configuration)"

############################
#
#          CLEAN
#
############################
			
clean:
	rm -f *.o
	
mrproper: clean
	rm -f $(EXEC)
	
# Fin Makefile
	
