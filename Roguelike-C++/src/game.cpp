#include <libtcod.hpp>
#include <iostream>
using namespace std;

class Character {
	private:
		int m_hp;
		int m_mp;
		int m_x;
		int m_y;
	
	public:
		Character(int x, int y) {
			m_hp = 100;
			m_mp = 0;
			m_x = x;
			m_y = y;
		};
		
		int hp() { return m_hp; };
		int mp() { return m_mp; };
		int x() { return m_x; };
		int y() { return m_y; };
		
		void Move(int x, int y);
};

void Character::Move(int xDelta, int yDelta) {
	m_x += xDelta;
	m_y += yDelta;
}

bool quitGame = false;

int main(void) {
	TCODConsole::initRoot(80, 50, "libtcod C++ sample", false);
	// TCODConsole::credits();
	
	TCODConsole::root->setBackgroundColor(TCODColor::black);
	TCODConsole::root->setForegroundColor(TCODColor::white);
	
	Character player(1, 1);
	
	while(!quitGame and !TCODConsole::isWindowClosed()) {
		TCODConsole::root->clear();
		
		TCODConsole::root->putChar(player.x(), player.y(), '@', TCOD_BKGND_SET);
		
		TCODConsole::flush();
		
		TCOD_key_t key = TCODConsole::waitForKeypress(true);
		switch (key.vk) {
			case TCODK_ESCAPE:
				quitGame = true;
				break;
			
			case TCODK_KP4:
				player.Move(-1, 0);
				break;
			
			default:
				break;
		}
	}
	
	return 0;
}
