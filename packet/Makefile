# Makefile des packets
#
# Auteur: LEBOURGEOIS Quentin et réutilisé par Olivier !
# Date: jeu. 5 avril 2012
# Version: 
#

CC=g++
CFLAGS=-Wall -ggdb -I../tcp/include/ -I../filemanager/include/ -Iinclude/
LDFLAGS=
EXEC=protocol
SRC=src/
INC=include/

FM=../filemanager/

all: protocol

# Edition des liens
protocol: Data.o Packet.o PacketReady.o PacketAreYouReady.o PacketMd5Error.o PacketSendChunk.o PacketSendOperation.o PacketNewFile.o PacketChunkReceived.o PacketCallback.o Chunk.o main.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation du conteneur Data
Data.o: $(SRC)Data.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du Packet
Packet.o: $(SRC)Packet.cpp
	$(CC) -c $^ $(CFLAGS)
	
# Compilation du PacketReady
PacketReady.o: $(SRC)PacketReady.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du PacketReady
PacketAreYouReady.o: $(SRC)PacketAreYouReady.cpp
	$(CC) -c $^ $(CFLAGS)
	
# Compilation du PacketMd5Error
PacketMd5Error.o: $(SRC)PacketMd5Error.cpp
	$(CC) -c $^ $(CFLAGS)
	
# Compilation du PacketSendChunk
PacketSendChunk.o: $(SRC)PacketSendChunk.cpp
	$(CC) -c $^ $(CFLAGS)
	
# Compilation du PacketSendOperation
PacketSendOperation.o: $(SRC)PacketSendOperation.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du PacketChunkReceived
PacketChunkReceived.o: $(SRC)PacketChunkReceived.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du PacketNewFile
PacketNewFile.o: $(SRC)PacketNewFile.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du PacketManager
PacketCallback.o:  $(SRC)PacketCallback.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du Chunk
Chunk.o: $(FM)$(SRC)Chunk.cpp
	$(CC) -c $^ $(CFLAGS)
	
# Compilation du main
main.o: $(SRC)main.cpp
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f *.o
	
mrproper: clean
	rm -f $(EXEC)
	
# Fin Makefile
	
