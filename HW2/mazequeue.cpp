#include <iostream>
#include <queue>
using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	queue<Coord> coordQueue;
	Coord current(sr, sc);
	coordQueue.push(current);
	maze[sr][sc] = '@';
	while (!coordQueue.empty())
	{
		current = coordQueue.front();
		int r = current.r();
		int c = current.c();
		cout << "(" << r << "," << c << ")" << endl;
		coordQueue.pop();
		if (c == ec && r == er)
			return true;
		if (maze[r + 1][c] != 'X' && maze[r + 1][c] != '@')
		{
			Coord south(r + 1, c);
			coordQueue.push(south);
			maze[r + 1][c] = '@';
		}
		if (maze[r][c - 1] != 'X'&& maze[r][c - 1] != '@')
		{
			Coord west(r, c - 1);
			coordQueue.push(west);
			maze[r][c - 1] = '@';
		}
		if (maze[r - 1][c] != 'X' && maze[r - 1][c] != '@')
		{
			Coord north(r - 1, c);
			coordQueue.push(north);
			maze[r - 1][c] = '@';
		}
		if (maze[r][c + 1] != 'X' && maze[r][c + 1] != '@')
		{
			Coord east(r, c + 1);
			coordQueue.push(east);
			maze[r][c + 1] = '@';
		}
		
	}
	return false;
}


