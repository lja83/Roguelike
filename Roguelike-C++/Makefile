BUILDDIR=.
SRCDIR=src

LIBTCODDIR=./../libtcod-1.5.0
INCDIR=$(LIBTCODDIR)/include
LIBDIR=$(LIBTCODDIR)/lib
CFLAGS=$(FLAGS) -I$(INCDIR) -L$(LIBDIR) -Wall
CPP=mingw32-g++

all: game

game: game.o
	$(CPP) $(CFLAGS) $(SRCDIR)/game.o -ltcod-mingw -o $(BUILDDIR)/Game.exe
	cp $(LIBTCODDIR)/libtcod-mingw.dll $(BUILDDIR)
	cp $(LIBTCODDIR)/SDL.dll $(BUILDDIR)
	cp $(LIBTCODDIR)/terminal.png $(BUILDDIR)

game.o: $(SRCDIR)/game.cpp
	$(CPP) $(CFLAGS) -c $(SRCDIR)/game.cpp -o $(SRCDIR)/game.o

clean:
	rm $(SRCDIR)/*.o &
	rm $(BUILDDIR)/Game.exe &
	rm $(BUILDDIR)/SDL.dll &
	rm $(BUILDDIR)/libtcod-mingw.dll &
	rm $(BUILDDIR)/terminal.png
