#include <libtcod.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <sstream>

#include "Creature.h"
#include "Window.h"
using namespace std;

bool quitGame = false;

#define WIDTH 80
#define HEIGHT 50

vector<Creature> Creatures;
vector<Window> Windows;

int message_cursor = 1;
deque<string> Messages;

void write_message(const char *str) {
    Messages.push_front(str);
}

void render_map(Window *win) {
    TCODConsole *con = win->con();

    con->clear();
    for (unsigned int i = 0; i < Creatures.size(); i++) {
        Creature *tempChar = &Creatures[i];
        con->putChar(tempChar->x(), tempChar->y(), tempChar->symbol(), TCOD_BKGND_SET);
    }
}

void render_messages(Window *win) {
    TCODConsole *con = win->con();
    con->clear();
    int message_size = 0;
    int cursor_location = con->getHeight();
    int wrap_width = con->getWidth();

    string border = string(con->getWidth(), '-');
    con->printLeft(0, 0, TCOD_BKGND_SET, border.c_str());

    for(unsigned int i = 0; i < Messages.size(); i++) {
        message_size = con->getHeightLeftRect(0, 0, wrap_width, con->getHeight(), Messages[i].c_str());
        cursor_location -= message_size;
        if (cursor_location < 1) {
            break;
        }
        con->printLeftRect(0, cursor_location, wrap_width, con->getHeight(), TCOD_BKGND_SET, Messages[i].c_str());
    }
}

Window mainScreen(WIDTH, HEIGHT-10, render_map);
Window messageScreen(WIDTH, 10, render_messages);

void render_screen(void) {
    TCODConsole::root->clear();

    for(unsigned int i = 0; i < Windows.size(); i ++) {
        Window *tempWin = &Windows[i];
        tempWin->render();

        TCODConsole *tempCon = tempWin->con();
        TCODConsole::blit(tempCon, 0, 0, tempCon->getWidth(), tempCon->getHeight(), TCODConsole::root, tempWin->posX(), tempWin->posY());
        tempCon->clear();
    }
    
    TCODConsole::flush();
}

int main(void) {
    TCODConsole::initRoot(WIDTH, HEIGHT, "libtcod C++ sample", false);
    //TCODConsole::credits();
    
    TCODConsole::root->setBackgroundColor(TCODColor::black);
    TCODConsole::root->setForegroundColor(TCODColor::white);

    mainScreen.set_pos(0, 0);
    messageScreen.set_pos(0, mainScreen.con()->getHeight());

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
                KEY( TCODK_KP5,    write_message("Test message") )
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
