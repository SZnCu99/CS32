void listAll(const Domain* d, string path) // two-parameter overload
{
	if (d->subdomains().size() == 0)
	{
		cout << path << endl;
		return;
	}

	for (vector<Domain*>::size_type pos = 0; pos < d->subdomains().size(); pos++)
	{
		if (path != "")
		{
			listAll(d->subdomains()[pos], d->subdomains()[pos]->label() + "." + path);
		}
		else
		{
			listAll(d->subdomains()[pos], d->subdomains()[pos]->label());
		}
	}
}