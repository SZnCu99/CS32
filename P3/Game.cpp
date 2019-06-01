#include "Game.h"
#include "Player.h"
#include <iostream>

using namespace std;

Game::Game(const Board& b, Player* south, Player* north) : m_board(b),m_south(south),m_north(north),isSouthTurn(true)
{

}

void Game::display() const
{
	cout << "     "<< m_north->name() <<"     " << endl;
	for (int i = 1; i <= m_board.holes(); i++)
	{
		cout << " " << m_board.beans(NORTH, i);
	}
	cout << endl;
	cout << m_board.beans(NORTH, POT);
	for (int i = 0; i < m_board.holes(); i++)
	{
		cout << "  ";
	}
	cout << m_board.beans(SOUTH, POT) << endl;
	for (int i = 1; i <= m_board.holes(); i++)
	{
		cout << " " << m_board.beans(SOUTH, i);
	}
	cout << endl;
	cout << "     " << m_south->name() << "     " << endl;

}

void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
	if (m_board.beansInPlay(NORTH) == 0 || m_board.beansInPlay(SOUTH) == 0) //judge who is winner when the game is over
	{
		over = true;
		hasWinner = false;
		if (m_board.beans(NORTH, POT) != m_board.beans(SOUTH, POT))
		{
			hasWinner = true;
			if (m_board.beans(NORTH, POT) > m_board.beans(SOUTH, POT))
			{
				winner = NORTH;
			}
			else
			{
				winner = SOUTH;
			}
		}
	}
	else
	{
		over = false;
	}
}

bool Game::move()
{
	
	Side s = SOUTH;
	int hole = -1;
	int capture = 0;
	do
	{
		if (m_board.beansInPlay(NORTH) == 0 || m_board.beansInPlay(SOUTH) == 0)
		{
			if (m_board.beansInPlay(NORTH) == 0)
			{
				if (m_board.beansInPlay(SOUTH) != 0)
				{
					display();
					for (int i = 1; i <= m_board.holes(); i++)
					{

						m_board.moveToPot(SOUTH, i, SOUTH);

					}

					cout << "Sweeping all the beans into" << m_south->name() << "'s pot." << endl;
					display();
				}
			}

			else if (m_board.beansInPlay(SOUTH) == 0)
			{
				if (m_board.beansInPlay(NORTH) != 0)
				{
					display();
					for (int i = 1; i <= m_board.holes(); i++)
					{

						m_board.moveToPot(NORTH, i, NORTH);

					}

					cout << "Sweeping all the beans into" << m_north->name() << "'s pot." << endl;
					display();
				}
			}
			return false;
		}
		display();//?If the player gets an additional turn, 
		          //you should display the board so someone looking at the screen can follow what's happening
		if (isSouthTurn)
		{
			hole = m_south->chooseMove(m_board, SOUTH);
			if (!m_south->isInteractive())
			{
				cout << m_south->name() << " chooses hole " << hole << endl;
				//cin.ignore(10000, '\n');
			}

		}
		else
		{
			s = NORTH;
			hole = m_north->chooseMove(m_board, NORTH);
			if (!m_north->isInteractive())
			{
				cout << m_north->name() << " chooses hole " << hole << endl;
				//cin.ignore(10000, '\n');
			}
		}
		if (hole != -1)
		{
			capture = 1 + m_board.beans(s, hole)/(2 * m_board.holes() + 1);
			m_board.sow(s, hole, s, hole);
		}
	} while (hole == 0); // if there is an extra round,choose move again
	// s is now the end side

	if (m_board.beans(s, hole) == capture) // if the end hole was empty the moment ago
	{
		if ((isSouthTurn && s == SOUTH) || (!isSouthTurn && s == NORTH)) // if this hole is in my side
		{
			if (m_board.beans(opponent(s), hole) != 0)
			{
				m_board.moveToPot(s, hole, s);
				m_board.moveToPot(opponent(s), hole, s);
			}
		}
	}

	if (m_board.beansInPlay(NORTH) == 0)
	{
		if (m_board.beansInPlay(SOUTH) != 0)
		{
			display();
			for (int i = 1; i <= m_board.holes(); i++)
			{

				m_board.moveToPot(SOUTH, i, SOUTH);

			}

			cout << "Sweeping all the beans into" << m_south->name() << "'s pot." << endl;
			display();
		}
	}

	else if (m_board.beansInPlay(SOUTH) == 0)
	{
		if (m_board.beansInPlay(NORTH) != 0)
		{
			display();
			for (int i = 1; i <= m_board.holes(); i++)
			{

				m_board.moveToPot(NORTH, i, NORTH);

			}

			cout << "Sweeping all the beans into" << m_north->name() << "'s pot." << endl;
		}
	}

	isSouthTurn = !isSouthTurn;
	return true;


}

void Game::play()
{
	bool over, haswinner;
	Side winner;
	status(over, haswinner, winner);
	while (!over)
	{
		move();
		if (!m_north->isInteractive() && !m_south->isInteractive())
		{
			cin.ignore(10000, '\n');
		}
		status(over, haswinner, winner);
	}
	
	status(over, haswinner, winner);
	if (haswinner)
	{
		switch (winner)
		{
		case NORTH:
			display();
			cout << m_north->name() << " wins." << endl;
			break;
		case SOUTH:
			display();
			cout << m_south->name() << " wins." << endl;
			break;
		default:
			break;
		}
	}
	else
	{
		display();
		cout << "It's a tie." << endl;
	}

}

int Game::beans(Side s, int hole) const
{
	return m_board.beans(s, hole);
}