#include "Board.h"
#include "Side.h"
using namespace std;

Board::Board(int nHoles, int nInitialBeansPerHole)
	:m_holes(nHoles),m_initialBeans(nInitialBeansPerHole), m_total(nHoles * 2 + 2)
{
	if (m_holes <= 0)
		m_holes = 1;
	if (m_initialBeans < 0)
		m_initialBeans = 0;
	m_total = m_holes * 2 + 2;
	m_sides = vector<int> (m_holes * 2 + 2, m_initialBeans);
	m_sides.front() = 0;
	m_sides.at(m_holes + 1) = 0;
	
}


int Board::holes() const
{
	return m_holes;
}

int Board::beans(Side s, int hole) const
{
	if (hole > m_holes || hole < 0)
		return -1;

	int index = map(s, hole);
	return m_sides.at(index);
	
}

int Board::beansInPlay(Side s) const
{
	int count = 0;
	for (int i = 1; i < m_holes + 1; i++)
	{
		count += beans(s, i);
	}
	return count;
}

int Board::totalBeans() const
{
	return beansInPlay(SOUTH) + beansInPlay(NORTH) + beans(SOUTH, POT) + beans(NORTH, POT);
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
	int index = map(s, hole);
	if (index == -1 || hole == 0)
		return false;
	int beansLeft = beans(s, hole);  // count the number of beans in the hole
	 
	m_sides[index] = 0;  // remove the beans from the hole


	int currentHole = index + 1;
	int skip = 0; //determine which pot to skip
	switch (s)
	{
	case NORTH:
		skip = m_holes + 1;
		break;
	case SOUTH:
		break;
	default:
		break;
	}
	
	// circle the board counterclock wise until all the beans are sowed
	while (beansLeft > 0 && currentHole != m_total)
	{
		if (currentHole != skip)
		{
			m_sides[currentHole]++;
			beansLeft--;
		}
		currentHole++;
		
	}

	if (beansLeft > 0)
	{
		currentHole = 0;
		while (beansLeft > 0)
		{
			if (currentHole != skip)
			{
				m_sides[currentHole]++;
				beansLeft--;
			}
			currentHole++;
			if (currentHole >= m_total)
			{
				currentHole = 0;
			}
		}
	}

	if (currentHole > 0)
	{
		currentHole--;
	}
	else
	{
		currentHole = m_total - 1;
	}

	map(currentHole, endSide, endHole);// convert where the last index to the hole
	return true;

}

bool Board::moveToPot(Side s, int hole, Side potOwner)
{
	int index = map(s, hole);
	if (index == -1 || hole == 0) //invalide hole or pot
	    return false;
	int num = beans(s, hole);
	m_sides[index] = 0; // remove the beans in the holes 
	int pot = 0;
	switch (potOwner) // find the index of the pot
	{
	case NORTH:
		pot = 0;
		break;
	case SOUTH:
		pot = m_holes+1;
		break;
	default:
		break;
	}
	m_sides[pot] += num; // move to the pot
	return true;
}

bool Board::setBeans(Side s, int hole, int beans)
{
	if (hole > m_holes || hole < 0 || beans < 0)
	    return false;
	int index = map(s, hole);
	m_sides[index] = beans;
	return true;
}

int Board::map(Side s, int holes) const
{
	if (holes < 0 || holes > m_holes)
		return -1; // if the hole is invalid 
	if (s == SOUTH)
	{
		if (holes == 0)
			holes = m_holes+1;
		return holes;
	}
	if (s == NORTH)
	{
		if (holes == 0)
			holes = m_total;
		return m_total - holes;
	}
	else
		return -1;
}

void Board::map(int index, Side& s, int& holes) const
{
	if (index < 0 || index >= m_total)
	{
		
		return;
	}
	if (index <= (m_holes + 1) && index > 0)
	{
		s = SOUTH;
		if (index != (m_holes+1) )
			holes = index;
		else
			holes = 0;
		return;
	}
	if (((index < m_total) && (index >(m_holes + 1))) || index == 0)
	{
		s = NORTH;
		if (index != 0)
			holes = m_total - index;
		else
			holes = 0;
		return;
	}

}
