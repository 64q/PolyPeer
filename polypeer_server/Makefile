# Makefile des packets
#
# Auteur: LEBOURGEOIS Quentin et réutilisé par Charles
# Date: jeu. 5 avril 2012
# Version: 
#

CC=g++
CFLAGS=-Wall -Iinclude/ -I../server/include/ -I../logger/include/ -I../XMLTool/include/tinyxml/ -I../XMLTool/include/ -I../filemanager/include/ -I../packet/include/ -I../connection/include/ -I../tcp/include/ -I../tcp/include/Exceptions/ -D TIXML_USE_STL
LDFLAGS=-lpthread
EXEC=polypeer
SRC=src/
INC=include/

FM =../filemanager/
P = ../packet/
C = ../connection/
T = ../tcp/
XML=../XMLTool/
TinyXML=../XMLTool/include/tinyxml/
LOG=../logger/

all: $(EXEC)



############################
#
#          MAIN
#
############################

# Compilation du main
main.o: $(SRC)main.cpp
	$(CC) -c $^ $(CFLAGS)

############################
#
#     SERVEUR PolyPeer
#
############################

# Compilation du serveur PolyPeer
PolypeerServer.o: $(SRC)PolypeerServer.cpp
	$(CC) -c $^ $(CFLAGS)

############################
#
#       WEB SERVEUR
#
############################


############################
#
#   STRUCTURE PRINCIPALE
#
############################

MainStruct=Zone.o Host.o Entity.o File.o DeploymentState.o XMLTool.o ServerData.o

# Compilation de Zone
Zone.o: $(XML)$(SRC)Zone.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de Host
Host.o: $(XML)$(SRC)Host.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de Entity
Entity.o: $(XML)$(SRC)Entity.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de File
File.o: $(XML)$(SRC)File.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de DeploymentState
DeploymentState.o: $(XML)$(SRC)DeploymentState.cpp
	$(CC) -c $^ $(CFLAGS)
	
# Compilation de XMLTool
XMLTool.o: $(XML)$(SRC)XMLTool.cpp
	$(CC) -c $^ $(CFLAGS)
	
# Compilation de ServerData
ServerData.o: $(XML)$(SRC)ServerData.cpp
	$(CC) -c $^ $(CFLAGS)



############################
#
#    LIBRAIRY TINY XML
#
############################

LibXML=tinyxml.o tinyxmlparser.o tinyxmlerror.o tinystr.o
	
# Compilation de tinyxml
tinyxml.o: $(TinyXML)tinyxml.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de tinyxmlparser
tinyxmlparser.o: $(TinyXML)tinyxmlparser.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de tinyxmlerror
tinyxmlerror.o: $(TinyXML)tinyxmlerror.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de tinystr
tinystr.o: $(TinyXML)tinystr.cpp
	$(CC) -c $^ $(CFLAGS)
	

############################
#
#       FILEMANAGER
#
############################

FileManager=FileManager.o Chunk.o

# Compilation du Chunk
Chunk.o: $(FM)$(SRC)Chunk.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du FileManager
FileManager.o: $(FM)$(SRC)FileManager.cpp
	$(CC) -c $^ $(CFLAGS)


############################
#
#     PACKET::PROTOCOL
#
############################

PacketManager=Data.o Packet.o PacketReady.o PacketDiskFull.o PacketSendOperationFinished.o PacketMd5Error.o PacketSendChunk.o PacketSendOperation.o PacketChunkReceived.o PacketNewFile.o

# Compilation de Data
Data.o: $(P)$(SRC)Data.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du Packet
Packet.o: $(P)$(SRC)Packet.cpp
	$(CC) -c $^ $(CFLAGS)
	
# Compilation du PacketReady
PacketReady.o: $(P)$(SRC)PacketReady.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du PacketDiskFull
PacketDiskFull.o: $(P)$(SRC)PacketDiskFull.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du PacketSendOperationFinished
PacketSendOperationFinished.o: $(P)$(SRC)PacketSendOperationFinished.cpp
	$(CC) -c $^ $(CFLAGS)
	
# Compilation du PacketMd5Error
PacketMd5Error.o: $(P)$(SRC)PacketMd5Error.cpp
	$(CC) -c $^ $(CFLAGS)
	
# Compilation du PacketSendChunk
PacketSendChunk.o: $(P)$(SRC)PacketSendChunk.cpp
	$(CC) -c $^ $(CFLAGS)
	
# Compilation du PacketSendOperation
PacketSendOperation.o: $(P)$(SRC)PacketSendOperation.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du PacketChunkReceived
PacketChunkReceived.o: $(P)$(SRC)PacketChunkReceived.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du PacketNewFile
PacketNewFile.o: $(P)$(SRC)PacketNewFile.cpp
	$(CC) -c $^ $(CFLAGS)


############################
#
#      CALLBACK MANAGER
#
############################

CallbackManager=PacketCallback.o callbackFunction.o

# Compilation du PacketManager
PacketCallback.o:  $(P)$(SRC)PacketCallback.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du callbackFunction
callbackFunction.o: $(P)$(SRC)callbackFunction.cpp
	$(CC) -c $^ $(CFLAGS)

############################
#
#    CONNECTION MANAGER
#
############################

ConnectionManager=ConnectionManager.o Connection.o BaseSocket.o ServerSocket.o Socket.o


# Compilation du ConnectionManager
ConnectionManager.o: $(C)$(SRC)ConnectionManager.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de Connection
Connection.o: $(C)$(SRC)Connection.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du BaseSocket
BaseSocket.o: $(T)$(SRC)BaseSocket.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du ServerSocket
ServerSocket.o: $(T)$(SRC)ServerSocket.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du Socket
Socket.o: $(T)$(SRC)Socket.cpp
	$(CC) -c $^ $(CFLAGS)


############################
#
#      LOGGER
#
############################

Logger=Logger.o

# Compilation du Logger
Logger.o:  $(LOG)$(SRC)Logger.cpp
	$(CC) -c $^ $(CFLAGS)


############################
#
#    EDITION DES LIENS
#    CREATION DE L'EXE
#
############################


polypeer: main.o PolypeerServer.o $(MainStruct) $(LibXML) $(FileManager) $(PacketManager) $(CallbackManager) $(ConnectionManager) $(Logger)
	$(CC) -o $@  $^ $(LDFLAGS)


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
	
