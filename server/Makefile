# Makefile du server
#
# Auteur: LEBOURGEOIS Quentin
# Date: sam. 07 avril 2012
# Version: 
#

CC=g++
CFLAGS=-Wall -ggdb -I../tcp/include/ -I../webserver/include/ -I../filemanager/include/ -I../logger/include/ -Iinclude/
LDFLAGS=
EXEC=server
SRC=src/

# les autres où chercher les fichiers
WS=../webserver/
TCP=../tcp/
LOGGER=../logger/
FM=../filemanager/

all: $(EXEC)

# Edition des liens
server: Server.o BaseServer.o Entity.o Zone.o WebServer.o WebResponse.o WebRequest.o TinyParser.o BaseSocket.o ServerSocket.o Socket.o Logger.o Host.o DeploymentState.o routes.o server.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation du BaseServer
BaseServer.o: $(SRC)BaseServer.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du server
Server.o: $(SRC)Server.cpp
	$(CC) -c $^ $(CFLAGS)

Entity.o: $(SRC)Entity.cpp
	$(CC) -c $^ $(CFLAGS)

Host.o: $(SRC)Host.cpp
	$(CC) -c $^ $(CFLAGS)
	
Zone.o: $(SRC)Zone.cpp
	$(CC) -c $^ $(CFLAGS)
	
DeploymentState.o: $(SRC)DeploymentState.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du webserver
WebServer.o: $(WS)$(SRC)WebServer.cpp
	$(CC) -c $^ $(CFLAGS)

WebResponse.o: $(WS)$(SRC)WebResponse.cpp
	$(CC) -c $^ $(CFLAGS)
	
WebRequest.o: $(WS)$(SRC)WebRequest.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation des routes
routes.o: $(WS)$(SRC)routes.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du Parser
TinyParser.o: $(WS)$(SRC)TinyParser.cpp
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

# Compilation du Logger
Logger.o: $(LOGGER)$(SRC)Logger.cpp
	$(CC) -c $^ $(CFLAGS)
	
# Compilation du Chunk
Chunk.o: $(FM)$(SRC)Chunk.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du FileManager
FileManager.o: $(FM)$(SRC)FileManager.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du fichier de main
server.o: $(SRC)server.cpp
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f *.o
	
mrproper: clean
	rm -f $(EXEC)
	
# Fin Makefile
	
