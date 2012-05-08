# Makefile des packets
#
# Auteur: LEBOURGEOIS Quentin et réutilisé par Olivier !
# Date: jeu. 5 avril 2012
# Version: 
#

CC=g++
CFLAGS=-Wall -ggdb -Iinclude/ -Iinclude/tinyxml -D TIXML_USE_STL
LDFLAGS=
EXEC=xml
SRC=src/
INC=include/

FM=../filemanager/

all: xml

# Edition des liens
xml: Host.o Zone.o File.o DeploymentState.o Entity.o XMLTool.o tinyxml.o tinyxmlparser.o tinyxmlerror.o tinystr.o main.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation de XMLTool
XMLTool.o: $(SRC)XMLTool.cpp
	$(CC) -c $^ $(CFLAGS)
	
# Compilation de Entity
Entity.o: $(SRC)Entity.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de DeploymentState
DeploymentState.o: $(SRC)DeploymentState.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de File
File.o: $(SRC)File.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de Zone
Zone.o: $(SRC)Zone.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de Host
Host.o: $(SRC)Host.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation du main
main.o: $(SRC)main.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de tinyxml
tinyxml.o: $(INC)tinyxml/tinyxml.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de tinyxmlparser
tinyxmlparser.o: $(INC)tinyxml/tinyxmlparser.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de tinyxmlerror
tinyxmlerror.o: $(INC)tinyxml/tinyxmlerror.cpp
	$(CC) -c $^ $(CFLAGS)

# Compilation de tinystr
tinystr.o: $(INC)tinyxml/tinystr.cpp
	$(CC) -c $^ $(CFLAGS)
			
clean:
	rm -f *.o
	
mrproper: clean
	rm -f $(EXEC)
	
# Fin Makefile
	
