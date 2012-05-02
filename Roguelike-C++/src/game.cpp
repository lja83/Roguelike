#include <libtcod.hpp>

int main(void) {
	TCODConsole::initRoot(80, 50, "libtcod C++ sample", false);
	TCODConsole::credits();
	
	return 0;
}
