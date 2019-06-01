#ifndef BOA_H
#define BOA_H

#include<vector>
#include"Side.h"

class Board
{
public:
	Board(int nHoles, int nInitialBeansPerHole);
	int holes() const;
	int beans(Side s, int hole) const;
	int beansInPlay(Side s) const;
	int totalBeans() const;
	bool sow(Side s, int hole, Side& endSide, int& endHole);
	bool moveToPot(Side s, int hole, Side potOwner);
	bool setBeans(Side s, int hole, int beans);

private:
	int m_holes;
	int m_initialBeans;
	int m_total;
	std::vector<int> m_sides;
	int map(Side s, int holes) const; // convert the hole into an index of the vector
	void map(int index, Side& s, int& holes) const; //convert index of the vector to a hole

};



#endif // !BOA_H
