# Makefile du webserver
#
# Auteur: LEBOURGEOIS Quentin
# Date: jeu. 29 mars 2012
# Version: 
#

CC=g++
CFLAGS=-Wall -ggdb
LDFLAGS=
EXEC=webserver
SRC=src/
INC=include/

all: webserver

# Edition des liens
webserver: WebServer.o WebResponse.o WebRequest.o TinyParser.o server.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation du server
WebServer.o: $(SRC)WebServer.cpp
	$(CC) -c $^ $(CFLAGS)

WebResponse.o: $(SRC)WebResponse.cpp
	$(CC) -c $^ $(CFLAGS)
	
WebRequest.o: $(SRC)WebRequest.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du Parser
TinyParser.o: $(SRC)TinyParser.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du fichier de main
server.o: $(SRC)server.cpp
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f *.o
	
mrproper: clean
	rm -f $(EXEC)
	
# Fin Makefile
	
