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
Creature *player = NULL;

vector<Window> Windows;

deque<string> Messages;

class Tile {
private:
    char m_symbol;
    bool m_blocking;
    bool m_transparent;
public:
    char symbol()      { return m_symbol; };
    bool blocking()    { return m_blocking; };
    bool transparent() { return m_transparent; };

    void symbol(char newSymbol)           { m_symbol = newSymbol; };
    void blocking(bool newBlocking)       { m_blocking = newBlocking; };
    void transparent(bool newTransparent) { m_transparent = newTransparent; };
};

class Map {
private:
    int m_width;
    int m_height;
    vector<Tile> m_tiles;
public:
    Map(string bareMap);

    int width()  { return m_width; };
    int height() { return m_height; };

    void width(int newWidth)   { m_width = newWidth; };
    void height(int newHeight) { m_height = newHeight; };
};

Map::Map(string bareMap) {
    int w = 0;
    int h = 0;

    char temp = bareMap[(h*w)+w];
    while(bareMap[(h*w) + w] != NULL) {
        if (temp == '\n') {
            h++;
            w = 0;
        } else {
            w ++;
            cout << temp;
        }
        temp = bareMap[(h*w)+w];
    }
    cout << endl << w << ' ' << h;
}

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

void move_creature(Creature *creature, int x, int y) {
    int newX = creature->x() + x;
    int newY = creature->y() + y;

    if ((newX < 0) || (newX >= mainScreen.con()->getWidth())) {
        x = 0;
    }
    if ((newY < 0) || (newY >= mainScreen.con()->getHeight())) {
        y = 0;
    }

    creature->Move(x, y);
}

void handle_command(TCOD_key_t key) {
    switch (key.vk) {
        
        #define KEY(keycode, func) case keycode: func; break;
            KEY( TCODK_ESCAPE, quitGame = true;     )
            KEY( TCODK_KP1,    move_creature(player, -1,  1) )
            KEY( TCODK_KP2,    move_creature(player,  0,  1) )
            KEY( TCODK_KP3,    move_creature(player,  1,  1) )
            KEY( TCODK_KP4,    move_creature(player, -1,  0) )
            KEY( TCODK_KP5,    write_message("Test message") )
            KEY( TCODK_KP6,    move_creature(player,  1,  0) )
            KEY( TCODK_KP7,    move_creature(player, -1, -1) )
            KEY( TCODK_KP8,    move_creature(player,  0, -1) )
            KEY( TCODK_KP9,    move_creature(player,  1, -1) )
        #undef KEY
        
        default:
            break;
    }
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
    
    player = &Creatures[0];
    
    while(!quitGame && !TCODConsole::isWindowClosed()) {
        render_screen();

        TCOD_key_t key = TCODConsole::waitForKeypress(true);
        handle_command(key);
    }
    
    Map newMap("Something\nNew");

    return 0;
}
