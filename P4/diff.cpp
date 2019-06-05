#include<iostream>
#include<fstream>
#include <string>
#include <queue>
#include <vector>
#include "Hash.h"

using namespace std;

void read(istream& file, string& s)
{
	s = "";
	char add;
	while (file.get(add))
	{
		s += add;
	}
}

void store(const string& old, Hash& table)
{
	for (long i = 0; (i + SIZE) <= old.size(); i++)
	{
		string s = old.substr(i, SIZE);
		table.insert(s, i);
	}
}

void mergeAdd(const std::string& news, long& length,const long& pos, const Hash& table)
{
	if (pos + SIZE > news.size())
	{
		length = length + news.size()-pos;
		return;
	}
	string current = news.substr(pos, SIZE);
	vector<long> result;
	if (table.search(current,result))
	{
		return;
	}

	length += 1;
	mergeAdd(news, length, pos + 1, table);
}

void mergeCopy(const std::string& news, const std::string& olds, long& length, const long& oldpos, const long& newpos)
{
	if (newpos >= news.size() || oldpos >= olds.size())
	{
		return;
	}

	if (news[newpos] == olds[oldpos])
	{
		length += 1;
		mergeCopy(news, olds, length, oldpos + 1, newpos + 1);
		return;
	}

	if (news[newpos] != olds[oldpos])
	{
		return;
	}

	

}

long bestOffset(const std::vector<long>& offsets, const std::string& news, const std::string& olds, const long& newpos)
{
	long maxlen(0), currentlen(0),offset(offsets[0]);
	for (int i = 0; i < offsets.size(); i++)
	{
		currentlen = 0;
		mergeCopy(news, olds, currentlen, offsets[i]+SIZE,newpos);
		if (currentlen > maxlen)
		{
			maxlen = currentlen;
			offset = offsets[i];
		}

	}
	return offset;
}

void createDiff(istream& fold, istream& fnew, ostream& fdiff)
{
	string olds(""), news("");
	read(fold, olds);
	read(fnew, news);
	Hash table;
	store(olds, table);
	long pos(0);
	string diff = "";
	//todo: repeated 8 byte value
	while (pos < news.size())
	{
		

		long addlen(0),copylen(SIZE);
		bool isFound = false;
		vector<long> offsets;
		if (pos + SIZE <= news.size())
		{
			string current = news.substr(pos, SIZE);
		    isFound = table.search(current,offsets);
		}

		if (isFound)
		{
			
			long offset = bestOffset(offsets, news, olds, pos+SIZE);
			mergeCopy(news, olds, copylen, offset + SIZE, pos+SIZE);
			diff = diff + "C" + to_string(copylen) + "," + to_string(offset);
			pos += copylen;
		}


		if (!isFound)
		{
			mergeAdd(news, addlen, pos, table);
			diff = diff + "A" + to_string(addlen) + ":" + news.substr(pos, addlen);
			pos = pos + addlen;
		}

	}
	fdiff << diff;





}

bool applyDiff(istream& fold, istream& fdiff, ostream& fnew)
{
	string olds(""), diff(""), news("");
	read(fold, olds);
	read(fdiff, diff);
	queue<char> instruction;
	char now;
	long len(0),offset(-1);
	for (long pos = 0; pos < diff.size(); pos++)
	{
		instruction.push(diff[pos]);
	}

	while (!instruction.empty())
	{
		now = instruction.front();
		instruction.pop();
		switch (now)
		{
		case 'A':
			len = 0;
			now = instruction.front();
			instruction.pop();
			while (now >= '0' && now <= '9')
			{
				
				len = len * 10 + (now - '0');
				if (instruction.empty())
				{
					break;
				}
				now = instruction.front();
				instruction.pop();
			}
			if (now != ':')
			{
				return false;
			}
			
			for (long i = 0; i < len; i++)
			{
				now = instruction.front();
				instruction.pop();
				news += now;
			}
			break;
		case 'C':
			len = 0;
			offset = 0;
			now = instruction.front();
			instruction.pop();
			while (now >= '0' && now <= '9')
			{
				
				len = len * 10 + (now - '0');
				if (instruction.empty())
				{
					break;
				}
				now = instruction.front();
				instruction.pop();
			}
			if (now != ',')
			{
				return false;
			}
			now = instruction.front();
			
			while (now >= '0' && now <= '9')
			{

				instruction.pop();
				offset = offset * 10 + (now - '0');
				if (instruction.empty())
				{
					break;
				}
				now = instruction.front();
			}
			news += olds.substr(offset, len);
			break;
		case '\n':
		case '\r':
			break;
		default:
			return false;
			break;
		}
	}

	fnew << news;
	return true;

}



