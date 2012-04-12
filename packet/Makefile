# Makefile du filemanager
#
# Auteur: LEBOURGEOIS Quentin et réutilisé par Olivier !
# Date: jeu. 5 avril 2012
# Version: 
#

CC=g++
CFLAGS=-Wall -ggdb -I../tcp/include/ -I../webserver/include/ -I../filemanager/include/ -I../logger/include/ -Iinclude/
LDFLAGS=
EXEC=packet
SRC=src/
INC=include/

all: protocol

# Edition des liens
protocol: Data.o main.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation du Chunk
Data.o: $(SRC)Data.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du FileManager
Packet.o: $(SRC)Packet.cpp
	$(CC) -c $^ $(CFLAGS)
	
# Compilation du main
main.o: $(SRC)main.cpp
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f *.o
	
mrproper: clean
	rm -f $(EXEC)
	
# Fin Makefile
	
