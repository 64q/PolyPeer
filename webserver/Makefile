# Makefile du webserver
#
# Auteur: LEBOURGEOIS Quentin
# Date: jeu. 29 mars 2012
# Version: 
#

# les autres où chercher les fichiers
LOGGER=../logger/
SRV=../ppserver/

# Définitions des autres variables
CC=g++
CFLAGS=-Wall -ggdb -I$(LOGGER)include/ -Iinclude/ -I$(SRV)include/
LDFLAGS=-pthread -ldl
EXEC=webserver
SRC=src/
INC=include/

all: webserver

# Edition des liens
webserver: WebServer.o Logger.o server.o BaseServer.o mongoose.o routes.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation des routes
routes.o: $(SRC)routes.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du server
WebServer.o: $(SRC)WebServer.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du BaseServer
BaseServer.o: $(SRV)$(SRC)BaseServer.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du Logger
Logger.o: $(LOGGER)$(SRC)Logger.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du fichier de main
server.o: $(SRC)server.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de mongoose
mongoose.o: $(SRC)mongoose.c
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f *.o
	
mrproper: clean
	rm -f $(EXEC)
	
# Fin Makefile
	
