BUILDDIR=./../

LIBTCODDIR=./../../libtcod-1.5.0
INCDIR=$(LIBTCODDIR)/include
LIBDIR=$(LIBTCODDIR)/lib
CFLAGS=$(FLAGS) -I$(INCDIR) -L$(LIBDIR) -Wall
CPP=mingw32-g++

all: game

game: game.o Creature.o
	$(CPP) $(CFLAGS) *.o -ltcod-mingw -o $(BUILDDIR)/Game.exe

game.o: game.cpp
	$(CPP) $(CFLAGS) -c game.cpp -o game.o

Creature.o: Creature.cpp Creature.h
	$(CPP) $(CFLAGS) -c Creature.cpp -o Creature.o

clean:
	rm *.o &
