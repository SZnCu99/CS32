#include "Player.h"
#include <string>
#include<iostream>
using namespace std;




std::string Player::name() const
{
	return m_name;
}

bool Player::isInteractive() const
{
	return false;
}


int HumanPlayer::chooseMove(const Board& b, Side s) const
{
	if (b.beansInPlay(s) == 0)
		return -1; // if the game is over
	int hole = -1;
	cout << "Select a hole, " << name() << ":";
	cin >> hole;
	while (hole <= 0 || hole > b.holes())
	{
		cout << "Select a hole, " << name() << ":";
		cin >> hole;
	}
	while (b.beans(s, hole) == 0)
	{
		cout << "There is no bean in that hole" << endl;
		cout << "Select a hole, " << name() << ":";
		cin >> hole;
	}
	return hole;
}

int BadPlayer::chooseMove(const Board& b, Side s) const
{
	for (int i = 1; i <= b.holes(); i++) // always choose the first hole
	{
		if (b.beans(s, i) != 0)
			return i;
	}
	return -1;
}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
	int difference = -999;
	int bestHole = -1;
	int depth = 0;
	AlarmClock ac(4900);
	choose(s, b, bestHole, difference, depth,ac);
	return bestHole;

}

void SmartPlayer::choose(Side s, const Board& b, int& bestHole, int& difference, const int& depth, AlarmClock& ac) const
{
	if (b.beansInPlay(s) == 0 || b.beansInPlay(opponent(s)) == 0)
	{
		bestHole = -1;
		difference = evaluate(b, s, depth);
		return;
	}
	if (depth >= m_depth || ac.timedOut())
	{
		bestHole = -1;
		difference = evaluate(b, s, depth);
		return;
	}
	Board temp = b;
	Side endSide;
	int endHole;
	int capture;
	int compare = (-100) * whichSide(depth);
	int nextD, nextBest;
	for (int i = 1; i <= temp.holes(); i++)
	{
		if (temp.beans(s, i) == 0)
		{
			continue;
		}
		/*if (s == NORTH)
		{
			int extra = temp.beans(s, i) - i;
			if (extra == 0)
			{
				bestHole = i;
				difference = evaluate(b, s, depth);
				return;
			}
		}
		if (s == SOUTH)
		{
			int extra = temp.beans(s, i) - temp.holes() + i - 1;
			if (extra == 0)
			{
				bestHole = i;
				difference = evaluate(b, s, depth);
				return;
			}
		}*/
		temp.sow(s, i, endSide, endHole);
		while (endHole == 0) // if there is an extra round
		{
			choose(s, temp, nextBest, nextD, depth, ac);
			if (!temp.sow(s, nextBest, endSide, endHole))
			{
				break;
			}
		}
		capture = 1 + temp.beans(endSide, endHole) / (2 * temp.holes() + 1);
		if (temp.beans(endSide, endHole) == capture && endSide == s && temp.beans(opponent(endSide),endHole)!= 0)
		{
			temp.moveToPot(endSide, endHole, s);
			temp.moveToPot(opponent(endSide), endHole, s);
		}
        ///make a complete move

		difference = evaluate(temp, s, depth);
		if (difference == whichSide(depth)*99)
		{
			bestHole = i;
			return;
		}
		choose(opponent(s), temp, nextBest, nextD, depth + 1, ac);
		temp = b; //unmake the move
		if (whichSide(depth) > 0 && nextD > compare)
		{
			bestHole = i;
			difference = nextD;
			compare = nextD;
		}
		else if (whichSide(depth) < 0 && nextD < compare)
		{
			bestHole = i;
			difference = nextD;
			compare = nextD;
		}
	
	}
	return;
}

int SmartPlayer::evaluate(const Board& b, const Side& s, const int& depth) const
{
	if (b.beansInPlay(s) == 0 || b.beansInPlay(opponent(s)) == 0) // if the game is over
	{
		if ((b.beans(s, POT) - b.beans(opponent(s), POT) + b.beansInPlay(s) - b.beansInPlay(opponent(s))) > 0)
		{
			return 99*whichSide(depth);
		}
		else if((b.beans(s, POT) - b.beans(opponent(s), POT) + b.beansInPlay(s) - b.beansInPlay(opponent(s))) < 0)
		{
			return -99*whichSide(depth);
		}
		else
		{
			return 0;
		}
	}

	

	return (b.beans(s, POT) - b.beans(opponent(s), POT))*whichSide(depth);
}

int SmartPlayer::whichSide(const int& depth) const
{
	return (2 * depth - (((depth + 1) / 2) * 4 - 1));
	//return 1 if its sp's turn, -1 if its sp's opponent's turn
}