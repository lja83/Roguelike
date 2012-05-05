#include <libtcod.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "Creature.h"
using namespace std;

bool quitGame = false;

#define WIDTH 80
#define HEIGHT 50

class Window {
private:
    int m_posX;
    int m_posY;

    TCODConsole *m_win;
public:
    Window(int width, int height) { m_win = new TCODConsole(width, height); };
    int posX() { return m_posX; };
    int posY() { return m_posY; };
    TCODConsole *win() { return m_win; };

    void set_pos(int x, int y) { m_posX = x; m_posY = y; };
};

vector<Creature> Creatures;
vector<Window> Windows;

Window mainScreen(WIDTH, HEIGHT-10);
Window messageScreen(WIDTH, 10);

void render_screen(void) {
    TCODConsole::root->clear();

    for(int i = 0; i < Creatures.size(); i ++) {
        Creature *tempChar = &Creatures[i];
        mainScreen.win()->putChar(tempChar->x(), tempChar->y(), tempChar->symbol(), TCOD_BKGND_SET);
    }

    string horizBorder(messageScreen.win()->getWidth(), '-');
    messageScreen.win()->printLeft(0, 0, TCOD_BKGND_SET, horizBorder.c_str());
    messageScreen.win()->printLeft(1, 1, TCOD_BKGND_SET, "This is a test");
    for(int i = 2; i < 10; i ++) {
        messageScreen.win()->printLeft(1, i, TCOD_BKGND_SET, "%d", i);
    }

    for(int i = 0; i < Windows.size(); i ++) {
        Window *tempWin = &Windows[i];
        TCODConsole *tempCon = tempWin->win();
        TCODConsole::blit(tempCon, 0, 0, tempCon->getWidth(), tempCon->getHeight(), TCODConsole::root, tempWin->posX(), tempWin->posY());
        tempCon->clear();
    }
    
    TCODConsole::flush();
}

int main(void) {
    TCODConsole::initRoot(WIDTH, HEIGHT, "libtcod C++ sample", false);
    TCODConsole::credits();
    
    TCODConsole::root->setBackgroundColor(TCODColor::black);
    TCODConsole::root->setForegroundColor(TCODColor::white);

    mainScreen.set_pos(0, 0);
    messageScreen.set_pos(0, mainScreen.win()->getHeight());

    Windows.push_back(mainScreen);
    Windows.push_back(messageScreen);

    Creatures.push_back(Creature('@', 1, 1));
    Creatures.push_back(Creature('O', 5, 5));
    
    Creature *player = &Creatures[0];
    
    while(!quitGame && !TCODConsole::isWindowClosed()) {
        render_screen();

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
