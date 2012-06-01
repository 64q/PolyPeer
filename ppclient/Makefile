# Makefile de céation du client polypeer
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
BASESERVER=../baseserver/
MUTEX=../mutex/

# Variables de nomage et de localisation
CC=g++
EXEC=ppclient
SRC=src/
INC=include/

# Flag pour le linker
LDFLAGS=-lpthread -pthread -ldl -g
# Flag préprocessing et compilation
CFLAGS=-Wall -I$(INC) -I$(FM)$(INC) -I$(PACKET)$(INC) -I$(DATA)$(INC) -I$(CB)$(INC) -I$(CONNECT)$(INC) -I$(TCP)$(INC) -I$(LOG)$(INC) -I$(XML)$(INC) -I$(TCPEXCEPT) -I$(TinyXML) -I$(BASESERVER)$(INC) -I$(MUTEX)$(INC) -D TIXML_USE_STL


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
#     CLIENT PolyPeer
#
############################

# Compilation du client Polypeer
PolypeerClient.o: $(SRC)PolypeerClient.cpp
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
#   STRUCTURE PRINCIPALE
#
############################

MainStruct=ClientData.o

# Compilation de ClientData
ClientData.o: $(XML)$(SRC)ClientData.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)


###########################
#
# MUTEX
#
###########################
Mutex=Mutex.o

# Compilation Mutex
Mutex.o: $(MUTEX)$(SRC)Mutex.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

############################
#
#    LIBRAIRY TINY XML
#
############################

	

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

CallbackManager=PacketCallback.o callbackFunctionClient.o

# Compilation du PacketManager
PacketCallback.o:  $(CB)$(SRC)PacketCallback.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

# Compilation du callbackFunctionClient
callbackFunctionClient.o: $(CB)$(SRC)callbackFunctionClient.cpp
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
#    EDITION DES LIENS
#    CREATION DE L'EXE
#
############################


$(EXEC): main.o PolypeerClient.o $(Mutex) $(BaseServ) $(MainStruct) $(FileManager) $(PacketManager) $(CallbackManager) $(Data) $(ConnectionManager) $(Logger)
	@echo "Link output files..."
	@$(CC) -o $@  $^ $(LDFLAGS)
	@echo "OK"
	@echo "Program name is $(EXEC)"


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
	
