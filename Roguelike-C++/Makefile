BUILDDIR=./
LIBTCODDIR=./../libtcod-1.5.0

all:
	cd src && make LIBTCODDIR="./../$(LIBTCODDIR)" BUILDDIR="./../$(BUILDDIR)"
	cp $(LIBTCODDIR)/libtcod-mingw.dll ./
	cp $(LIBTCODDIR)/SDL.dll ./
	cp $(LIBTCODDIR)/terminal.png ./

clean:
	cd src && make clean
	rm Game.exe &
	rm SDL.dll &
	rm libtcod-mingw.dll &
	rm terminal.png
