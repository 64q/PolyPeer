# Makefile du filemanager
#
# Auteur: LEBOURGEOIS Quentin
# Date: jeu. 5 avril 2012
# Version: 
#

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

# Variables de nomage et de localisation
CC=g++
EXEC=polypeer
SRC=src/
INC=include/

# Flag pour le linker
LDFLAGS=-lpthread -pthread -ldl -g
# Flag préprocessing et compilation
CFLAGS=-Wall -I$(INC) -I$(FM)$(INC) -I$(PACKET)$(INC) -I$(DATA)$(INC) -I$(CB)$(INC) -I$(CONNECT)$(INC) -I$(ALGO)$(INC) -I$(TCP)$(INC) -I$(LOG)$(INC) -I$(XML)$(INC) -I$(WEB)$(INC) -I$(TCPEXCEPT) -I$(TinyXML) -I$(BASESERVER)$(INC) -D TIXML_USE_STL



all: filemanager

# Edition des liens
filemanager: Chunk.o FileManager.o Data.o main.o
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
	
	
############################
#
#     	    DATA
#
############################

# Compilation de Data
Data.o: $(DATA)$(SRC)Data.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)
	
	

clean:
	rm -f *.o
	
mrproper: clean
	rm -f $(EXEC)
	
# Fin Makefile
	
