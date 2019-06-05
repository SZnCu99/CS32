#ifndef HAS_H
#define HAS_H

#include<list>
#include<algorithm>
#include<functional>
#include<string>
#include<vector>
#include<utility>
#include<cmath>

const long BUCKET_NUM = 99991;
const size_t SIZE = 8;




class Hash
{
public:
	Hash();
	bool search(const std::string& s, std::vector<long>& result) const;
	void insert(const std::string&s, const long offset);
	~Hash();
	


private:
	std::vector<std::list<std::pair<long, std::string>>*> m_buckets;



};




#endif // !HAS_H
