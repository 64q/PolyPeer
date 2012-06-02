# Makefile du logger
#
# Auteur: LEBOURGEOIS Quentin
# Date: jeu. 5 avril 2012
# Version: 
#

CC=g++
CFLAGS=-Wall -ggdb -Iinclude/ -I../mutex/include/
LDFLAGS=
EXEC=logger
SRC=src/
INC=include/

MUTEX=../mutex/

all: logger

# Edition des liens
logger: Logger.o Mutex.o example.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation du Logger
Logger.o: $(SRC)Logger.cpp
	$(CC) -c $^ $(CFLAGS)
	
# Compilation du main
example.o: $(SRC)example.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation des Mutex
Mutex.o:  $(MUTEX)$(SRC)Mutex.cpp
	@echo $^
	@$(CC) -c $^ $(CFLAGS)

clean:
	rm -f *.o
	
mrproper: clean
	rm -f $(EXEC)
	
# Fin Makefile
	
