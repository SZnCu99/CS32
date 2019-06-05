#ifndef DIF_H
#define DIF_H

#include<iostream>
#include<fstream>
#include <string>
#include "Hash.h"

void read(std::istream& file, std::string& s);
void store(const std::string& old, Hash& table);
void createDiff(std::istream& fold, std::istream& fnew, std::ostream& fdiff);
bool applyDiff(std::istream& fold, std::istream& fdiff, std::ostream& fnew);
void mergeAdd(const std::string& news, long& length,const long& pos, const Hash& table);
void mergeCopy(const std::string& news, const std::string& olds, long& length, const long& oldpos,const long& newpos);
long bestOffset(const std::vector<long>& offsets, const std::string& news, const std::string& olds, const long& newpos);



#endif // !DIF_H
