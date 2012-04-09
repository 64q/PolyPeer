# Makefile du filemanager
#
# Auteur: LEBOURGEOIS Quentin
# Date: jeu. 5 avril 2012
# Version: 
#

CC=g++
CFLAGS=-Wall -ggdb
LDFLAGS=
EXEC=filemanager
SRC=src/
INC=include/

all: filemanager

# Edition des liens
filemanager: Chunk.o FileManager.o main.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation du Chunk
Chunk.o: $(SRC)Chunk.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du FileManager
FileManager.o: $(SRC)FileManager.cpp
	$(CC) -c $^ $(CFLAGS)
	
# Compilation du main
main.o: $(SRC)main.cpp
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f *.o
	
mrproper: clean
	rm -f $(EXEC)
	
# Fin Makefile
	
