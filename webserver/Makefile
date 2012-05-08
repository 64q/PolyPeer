# Makefile du webserver
#
# Auteur: LEBOURGEOIS Quentin
# Date: jeu. 29 mars 2012
# Version: 
#

CC=g++
CFLAGS=-Wall -ggdb -I../tcp/include/ -I../logger/include/ -Iinclude/ -I../tcp/include/Exceptions/ -I../server/include/ -I../packet/include/
LDFLAGS=
EXEC=webserver
SRC=src/
INC=include/

# les autres où chercher les fichiers
TCP=../tcp/
LOGGER=../logger/
SRV=../server/
PACKET=../packet/

all: webserver

# Edition des liens
webserver: WebServer.o WebResponse.o WebRequest.o TinyParser.o BaseSocket.o ServerSocket.o Socket.o Logger.o routes.o server.o BaseServer.o Data.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation du server
WebServer.o: $(SRC)WebServer.cpp
	$(CC) -c $^ $(CFLAGS)

WebResponse.o: $(SRC)WebResponse.cpp
	$(CC) -c $^ $(CFLAGS)
	
WebRequest.o: $(SRC)WebRequest.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation des routes
routes.o: $(SRC)routes.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du Parser
TinyParser.o: $(SRC)TinyParser.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du BaseServer
BaseServer.o: $(SRV)$(SRC)BaseServer.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du BaseSocket
BaseSocket.o: $(TCP)$(SRC)BaseSocket.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du ServerSocket
ServerSocket.o: $(TCP)$(SRC)ServerSocket.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du Socket
Socket.o: $(TCP)$(SRC)Socket.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du Data
Data.o: $(PACKET)$(SRC)Data.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du Logger
Logger.o: $(LOGGER)$(SRC)Logger.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du fichier de main
server.o: $(SRC)server.cpp
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f *.o
	
mrproper: clean
	rm -f $(EXEC)
	
# Fin Makefile
	
