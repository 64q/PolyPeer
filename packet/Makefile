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
protocol: Data.o Packet.o PacketManager.o Chunk.o main.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation du conteneur Data
Data.o: $(SRC)Data.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du FileManager
Packet.o: $(SRC)Packet.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du PacketFactory
PacketManager.o:  $(SRC)PacketManager.cpp
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
	
