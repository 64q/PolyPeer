# Makefile du webserver
#
# Auteur: LEBOURGEOIS Quentin
# Date: jeu. 29 mars 2012
# Version: 
#

CC=g++
CFLAGS=-Wall -ggdb
LDFLAGS=
EXEC=tcp
SRC=src/
INC=include/

all: tcp

# Edition des liens
tcp: BaseSocket.o ServerSocket.o Socket.o main.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation du BaseSocket
BaseSocket.o: $(SRC)BaseSocket.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du ServerSocket
ServerSocket.o: $(SRC)ServerSocket.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du Socket
Socket.o: $(SRC)Socket.cpp
	$(CC) -c $^ $(CFLAGS)
	
# Compilation du main
main.o: $(SRC)main.cpp
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f *.o
	
mrproper: clean
	rm -f $(EXEC)
	
# Fin Makefile
	
