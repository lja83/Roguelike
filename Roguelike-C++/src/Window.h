#pragma once

class Window {
private:
    int m_posX;
    int m_posY;
    int m_scrollX;
    int m_scrollY;

    void (*m_render_func)(Window*);

    TCODConsole *m_con;
public:
    Window(int width, int height, void (*render_func)(Window*), int scrollX=0, int scrollY=0) { 
        m_con = new TCODConsole(width, height);
        m_posX = m_posY = m_scrollX = m_scrollY = 0;
        m_render_func = render_func;
    };
    int posX() { return m_posX; };
    int posY() { return m_posY; };
    TCODConsole *con() { return m_con; };

    void set_pos(int x, int y) { m_posX = x; m_posY = y; };
    void render() { (*m_render_func)(this); };
};
