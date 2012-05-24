# Makefile des packets
#
# Auteur: LEBOURGEOIS Quentin et réutilisé par Charles
# Date: jeu. 5 avril 2012
# Version: 
#

CC=g++
CFLAGS=-Wall -ggdb -Iinclude/ -Iinclude/tinyxml -I../filemanager/include/ -I../packet/include/ -I../connection/include/ -I../tcp/include/ -I../tcp/include/Exceptions -D TIXML_USE_STL
LDFLAGS=-lpthread
EXEC=xml
SRC=src/
INC=include/

FM =../filemanager/
P = ../packet/
C = ../connection/
T = ../tcp/

all: xml

# Edition des liens
xml: Host.o Zone.o File.o DeploymentState.o Entity.o ServerData.o XMLTool.o tinyxml.o tinyxmlparser.o tinyxmlerror.o tinystr.o Chunk.o FileManager.o Data.o ConnectionManager.o Connection.o BaseSocket.o ServerSocket.o Socket.o callbackFunction.o Packet.o PacketReady.o PacketDiskFull.o PacketSendOperationFinished.o PacketMd5Error.o PacketSendChunk.o PacketSendOperation.o PacketNewFile.o PacketChunkReceived.o PacketCallback.o main.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation de ServerData
ServerData.o: $(SRC)ServerData.cpp
	$(CC) -c $^ $(CFLAGS)
	
# Compilation de XMLTool
XMLTool.o: $(SRC)XMLTool.cpp
	$(CC) -c $^ $(CFLAGS)
	
# Compilation de Entity
Entity.o: $(SRC)Entity.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de DeploymentState
DeploymentState.o: $(SRC)DeploymentState.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de File
File.o: $(SRC)File.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de Zone
Zone.o: $(SRC)Zone.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de Host
Host.o: $(SRC)Host.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du main
main.o: $(SRC)main.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de tinyxml
tinyxml.o: $(INC)tinyxml/tinyxml.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de tinyxmlparser
tinyxmlparser.o: $(INC)tinyxml/tinyxmlparser.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de tinyxmlerror
tinyxmlerror.o: $(INC)tinyxml/tinyxmlerror.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de tinystr
tinystr.o: $(INC)tinyxml/tinystr.cpp
	$(CC) -c $^ $(CFLAGS)
	
# FileManager
# Compilation du Chunk
Chunk.o: $(FM)$(SRC)Chunk.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du FileManager
FileManager.o: $(FM)$(SRC)FileManager.cpp
	$(CC) -c $^ $(CFLAGS)

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

# Compilation du PacketManager
PacketCallback.o:  $(P)$(SRC)PacketCallback.cpp
	$(CC) -c $^ $(CFLAGS)

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
			
# Compilation du callbackFunction
callbackFunction.o: $(P)$(SRC)callbackFunction.cpp
	$(CC) -c $^ $(CFLAGS)
				
clean:
	rm -f *.o
	
mrproper: clean
	rm -f $(EXEC)
	
# Fin Makefile
	
