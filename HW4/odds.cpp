

void removeOdds(vector<int>& v)
{
	for (vector<int>::size_type i = 0; i < v.size(); i++)
	{
		if ((v[i] % 2) != 0)
		{
			vector<int>::iterator pos = v.begin() + i;
			v.erase(pos);
			i--;
		}
	}
}