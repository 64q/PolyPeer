# Makefile du webserver
#
# Auteur: LEBOURGEOIS Quentin
# Date: jeu. 29 mars 2012
# Version: 
#

CC=g++
CFLAGS=-Wall
LDFLAGS=
EXEC=webserver
SRC=src/
INC=include/

all: webserver

webserver: WebServer.o WebResponse.o WebRequest.o server.o
	$(CC) -o $@ $^ $(LDFLAGS)
	
WebServer.o: $(SRC)WebServer.cpp
	$(CC) -c $^ $(CFLAGS)

WebResponse.o: $(SRC)WebResponse.cpp
	$(CC) -c $^ $(CFLAGS)
	
WebRequest.o: $(SRC)WebRequest.cpp
	$(CC) -c $^ $(CFLAGS)

server.o: $(SRC)server.cpp
	$(CC) -c $^ $(CFLAGS)
	
clean:
	rm -f *.o
	
mrproper: clean
	rm -f $(EXEC)
	
# Fin Makefile
	
