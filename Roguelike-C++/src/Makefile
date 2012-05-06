INCDIR=$(LIBTCODDIR)/include
LIBDIR=$(LIBTCODDIR)/lib
CFLAGS=-I$(INCDIR) -Wall -c
LDFLAGS=-L$(LIBDIR) -ltcod-mingw
CPP=mingw32-g++

SOURCES=game.cpp Creature.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=$(BUILDDIR)/Game.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CPP) $(OBJECTS) -o $@ $(LDFLAGS)

-include $(OBJECTS:.o=.o.d)

.cpp.o:
	$(CPP) $(CFLAGS) $< -o $@
	$(CPP) -MM $(CFLAGS) $< > $@.d

clean:
	rm *.o *.d &
