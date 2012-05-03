#include <libtcod.hpp>
#include <iostream>
using namespace std;

#define MOVEKEY(keycode, x, y) case keycode: player.Move(x, y); break;

class Character {
    private:
        int  m_hp;
        int  m_mp;
        int  m_x;
        int  m_y;
        char m_symbol;
    
    public:
        Character(char symbol, int x, int y) {
            m_hp = 100;
            m_mp = 0;
            m_x =  x;
            m_y =  y;
            m_symbol = symbol;
        };
        
        int hp() { return m_hp; };
        int mp() { return m_mp; };
        int x()  { return m_x;  };
        int y()  { return m_y;  };
        
        char symbol() { return m_symbol; };
        void symbol(char newSymbol) { m_symbol = newSymbol; };
        
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
    
    Character player('@', 1, 1);
    
    while(!quitGame and !TCODConsole::isWindowClosed()) {
        TCODConsole::root->clear();
        
        TCODConsole::root->putChar(player.x(), player.y(), player.symbol(), TCOD_BKGND_SET);
        
        TCODConsole::flush();
        
        TCOD_key_t key = TCODConsole::waitForKeypress(true);
        switch (key.vk) {
             case TCODK_ESCAPE:
                 quitGame = true;
                 break;
            
            MOVEKEY( TCODK_KP4, -1,  0 )
            MOVEKEY( TCODK_KP6,  1,  0 )
            MOVEKEY( TCODK_KP8,  0, -1 )
            MOVEKEY( TCODK_KP2,  0,  1 )
            MOVEKEY( TCODK_KP7, -1, -1 )
            MOVEKEY( TCODK_KP9,  1, -1 )
            MOVEKEY( TCODK_KP1, -1,  1 )
            MOVEKEY( TCODK_KP3,  1,  1 )
            
            default:
                break;
        }
    }
    
    return 0;
}
