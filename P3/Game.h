#ifndef  GAM_H
#define GAM_H

#include "Board.h"
#include "Side.h"

class Player;

class Game
{
public:
	Game(const Board& b, Player* south, Player* north);
	void display() const;
	void status(bool& over, bool& hasWinner, Side& winner) const;
	bool move();
	void play();
	int beans(Side s, int hole) const;
private:
	Board m_board;
	Player* m_south;
	Player* m_north;
	bool isSouthTurn;
	
};


#endif // ! GAM_H
