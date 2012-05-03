#include <libtcod.hpp>

int main(void) {
	TCODConsole::initRoot(80, 50, "libtcod C++ sample", false);
	TCODConsole::root->credits();
	
	TCODConsole::root->setBackgroundColor(TCODColor::black);
	TCODConsole::root->setForegroundColor(TCODColor::white);
	
	while(!TCODConsole::isWindowClosed()) {
		TCODConsole::root->clear();
		
		TCOD_bkgnd_flag_t flag = TCOD_BKGND_SET;
		TCODConsole::root->putChar(1, 1, '@', flag);
		
		TCODConsole::root->flush();
	}
	
	return 0;
}
