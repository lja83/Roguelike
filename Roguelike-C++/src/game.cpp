#include <libtcod.hpp>
#include <iostream>
#include <vector>

#include "Creature.h"
using namespace std;

bool quitGame = false;

int main(void) {
    TCODConsole::initRoot(80, 50, "libtcod C++ sample", false);
    TCODConsole::credits();
    
    TCODConsole::root->setBackgroundColor(TCODColor::black);
    TCODConsole::root->setForegroundColor(TCODColor::white);

    vector<Creature> Creatures;
    Creatures.push_back(Creature('@', 1, 1));
    Creatures.push_back(Creature('O', 5, 5));
    
    Creature *player = &Creatures[0];
    
    while(!quitGame && !TCODConsole::isWindowClosed()) {
        TCODConsole::root->clear();
		
        for(int i = 0; i < Creatures.size(); i ++) {
            Creature *tempChar = &Creatures[i];
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
