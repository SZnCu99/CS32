
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
	Coord start(sr, sc);
	Coord end(er, ec);
	if (start.r() == end.r() && start.c() == end.c())
	{
		return true;
	}
	maze[sr][sc] = '@';
	if (maze[sr + 1][sc] != 'X' && maze[sr + 1][sc] != '@')
	{
		if (pathExists(maze, sr + 1, sc, er, ec))
		{
			return true;
		}
	}
	if (maze[sr][sc - 1] != 'X'&& maze[sr][sc - 1] != '@')
	{
		if(pathExists(maze, sr, sc - 1, er, ec))
			return true;
	}
	if (maze[sr - 1][sc] != 'X' && maze[sr - 1][sc] != '@')
	{
		if (pathExists(maze, sr - 1, sc, er, ec))
			return true;
	}
	if (maze[sr][sc + 1] != 'X' && maze[sr][sc + 1] != '@')
	{
		if(pathExists(maze, sr, sc+1, er, ec))
			return true;
	}
	return false;
}

