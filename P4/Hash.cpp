#include "Hash.h"
#include<vector>

using namespace std;



Hash::Hash()
{
	m_buckets = vector<list<pair<long, std::string>>*>(BUCKET_NUM, nullptr);
}



void Hash::insert(const string &s, const long offset)
{
	
	
	
	long key = hash<string>()(s);
	key = abs(key);
	long bucket = key % BUCKET_NUM;
	if (m_buckets[bucket] == nullptr)
	{
		m_buckets[bucket] = new list<pair<long, string>>;
	}
	pair<long, string> toInsert(offset, s);
	m_buckets[bucket]->push_back(toInsert);
	//m_buckets[bucket]->sort(isGreater);

	
}

bool Hash::search(const string& s,vector<long>& result) const
{
	bool isFound = false;
	if (s.size() != SIZE)
	{
		return false;
	}
	long key = hash<string>()(s);
	key = abs(key);
	long bucket = key % BUCKET_NUM;
	if (m_buckets[bucket] == nullptr)
	{
		return false;
	}
	for (list<pair<long, string>>::iterator i = m_buckets[bucket]->begin(); i != m_buckets[bucket]->end(); i++)
	{
		if (s == i->second)
		{
			result.push_back( i->first);
			isFound = true;
		}
	}
	return isFound;


}

Hash::~Hash()
{
	for (int i = 0; i < BUCKET_NUM; i++)
	{
		if (m_buckets[i] != nullptr)
		{
			delete m_buckets[i];
		}
	}
}