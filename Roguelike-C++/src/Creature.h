#pragma once

class Creature
{
private:
	int  m_hp;
	int  m_mp;
	int  m_x;
	int  m_y;
	char m_symbol;

public:
    Creature(char symbol='@', int x=1, int y=1) {
        m_hp = 100;
        m_mp = 0;
        m_x =  x;
        m_y =  y;
        m_symbol = symbol;
    };
	~Creature(void) {};

	int hp() { return m_hp; };
	int mp() { return m_mp; };
	int x()  { return m_x;  };
	int y()  { return m_y;  };
	
	char symbol() { return m_symbol; };
	void symbol(char newSymbol) { m_symbol = newSymbol; };
	
	void Move(int x, int y) { m_x += x; m_y += y; };
};