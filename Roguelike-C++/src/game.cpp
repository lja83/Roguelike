#include <libtcod.hpp>
#include <iostream>
#include <vector>
using namespace std;

class Character {
    private:
        int  m_hp;
        int  m_mp;
        int  m_x;
        int  m_y;
        char m_symbol;
    
    public:
        Character(char symbol='@', int x=1, int y=1) {
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
    TCODConsole::credits();
    
    TCODConsole::root->setBackgroundColor(TCODColor::black);
    TCODConsole::root->setForegroundColor(TCODColor::white);

    vector<Character> Characters;
    Characters.push_back(Character('@', 1, 1));
    Characters.push_back(Character('O', 5, 5));
    
    Character *player = &Characters[0];
    
    while(!quitGame && !TCODConsole::isWindowClosed()) {
        TCODConsole::root->clear();
		
        for(int i = 0; i < Characters.size(); i ++) {
            Character *tempChar = &Characters[i];
            TCODConsole::root->putChar(tempChar->x(), tempChar->y(), tempChar->symbol(), TCOD_BKGND_SET);
        }
        
        TCODConsole::flush();
        
        TCOD_key_t key = TCODConsole::waitForKeypress(true);
        switch (key.vk) {
            
            #define KEY(keycode, func) case keycode: func; break;
                KEY( TCODK_ESCAPE, quitGame = true;     )
                KEY( TCODK_KP1,    player->Move(-1,  1) )
                KEY( TCODK_KP2,    player->Move( 0,  1) )
                KEY( TCODK_KP3,    player->Move( 1,  1) )
                KEY( TCODK_KP4,    player->Move(-1,  0) )
                KEY( TCODK_KP5,    player->Move( 0,  0) )
                KEY( TCODK_KP6,    player->Move( 1,  0) )
                KEY( TCODK_KP7,    player->Move(-1, -1) )
                KEY( TCODK_KP8,    player->Move( 0, -1) )
                KEY( TCODK_KP9,    player->Move( 1, -1) )
            #undef KEY
            
            default:
                break;
        }
    }
    
    return 0;
}
