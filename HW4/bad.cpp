void removeBad(list<Movie*>& li)
{
	for (list<Movie*>::iterator pos = li.begin(); pos != li.end(); pos++)
	{
		if ((*pos)->rating() < 55)
		{
			list<Movie*>::iterator next = --pos;
			pos++;
			delete *pos;
			li.erase(pos);
			pos = next;
		}
	}
}

