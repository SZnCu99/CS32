//#include "Hash.h"
//#include"diff.h"
//#include <string>
//#include <iostream>
//#include <cassert>
//
//using namespace std;
//
//int main()
//{
//
//	
//
//	ifstream fold("G:/warandpeace1.txt");
//	if (!fold)
//	{
//		cout << "cannot open" << endl;
//		return(-1);
//
//	}
//	
//	/*ifstream infile("G:/warandpeace2.txt");
//	if (!fold)
//	{
//		cout << "cannot open" << endl;
//		return(-1);
//
//	}
//	ofstream outfile("G:/diff.txt");
//	if (!outfile)
//	{
//		cout << "cannot open" << endl;
//		return(-1);
//	}
//	createDiff(fold, infile, outfile);
//*/
//
//	//ofstream out("G:/my.txt");
//	//ifstream diff("G:/diff.txt");
//	//applyDiff(fold, diff, out);
//	
//	ifstream my("G:/my.txt");
//	ifstream given("G:/warandpeace2.txt");
//	string first(""), second("");
//	read(my, first);
//	read(given, second);
//	cout << (first == second);
//
//	
//}

//#include <iostream>
//#include <sstream>  // for istringstream and ostringstream
//#include <string>
//#include <cassert>
//#include "diff.h"
//
//using namespace std;
//
//void runtest(string oldtext, string newtext)
//{
//	istringstream oldFile(oldtext);
//	istringstream newFile(newtext);
//	ostringstream diffFile;
//	createDiff(oldFile, newFile, diffFile);
//	string result = diffFile.str();
//	cout << "The diff file length is " << result.size()
//		<< " and its text is " << endl;
//	cout << result << endl;
//
//	oldFile.clear();   // clear the end of file condition
//	oldFile.seekg(0);  // reset back to beginning of the stream
//	istringstream diffFile2(result);
//	ostringstream newFile2;
//	assert(applyDiff(oldFile, diffFile2, newFile2));
//	assert(newtext == newFile2.str());
//}
//
//int main()
//{
//	runtest("There's a bathroom on the right.",
//		"There's a bad moon on the rise.");
//	runtest("ABCDEFGHIJBLAHPQRSTUVPQRSTUV",
//		"XYABCDEFGHIJBLETCHPQRSTUVPQRSTQQELF");
//	cout << "All tests passed" << endl;
//}
//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <algorithm>
//#include <iterator>
//#include <cassert>
//#include "diff.h"
//using namespace std;
//
//bool runtest(string oldName, string newName, string diffName, string newName2)
//{
//	if (diffName == oldName || diffName == newName ||
//		newName2 == oldName || newName2 == diffName ||
//		newName2 == newName)
//	{
//		cerr << "Files used for output must have names distinct from other files" << endl;
//		return false;
//	}
//	ifstream oldFile(oldName, ios::binary);
//	if (!oldFile)
//	{
//		cerr << "Cannot open " << oldName << endl;
//		return false;
//	}
//	ifstream newFile(newName, ios::binary);
//	if (!newFile)
//	{
//		cerr << "Cannot open " << newName << endl;
//		return false;
//	}
//	ofstream diffFile(diffName, ios::binary);
//	if (!diffFile)
//	{
//		cerr << "Cannot create " << diffName << endl;
//		return false;
//	}
//	createDiff(oldFile, newFile, diffFile);
//	diffFile.close();
//
//	oldFile.clear();   // clear the end of file condition
//	oldFile.seekg(0);  // reset back to beginning of the file
//	ifstream diffFile2(diffName, ios::binary);
//	if (!diffFile2)
//	{
//		cerr << "Cannot read the " << diffName << " that was just created!" << endl;
//		return false;
//	}
//	ofstream newFile2(newName2, ios::binary);
//	if (!newFile2)
//	{
//		cerr << "Cannot create " << newName2 << endl;
//		return false;
//	}
//	assert(applyDiff(oldFile, diffFile2, newFile2));
//	newFile2.close();
//
//	newFile.clear();
//	newFile.seekg(0);
//	ifstream newFile3(newName2, ios::binary);
//	if (!newFile)
//	{
//		cerr << "Cannot open " << newName2 << endl;
//		return false;
//	}
//	if (!equal(istreambuf_iterator<char>(newFile), istreambuf_iterator<char>(),
//		istreambuf_iterator<char>(newFile3), istreambuf_iterator<char>()))
//	{
//
//		cerr << newName2 << " is not identical to " << newName
//			<< "; test FAILED" << endl;
//		return false;
//	}
//	return true;
//}
//
//int main()
//{
//	assert(runtest("G:/strange1.txt", "G:/strange2.txt", "G:/diff.txt", "G:/my.txt"));
//	cerr << "Test PASSED" << endl;
//}

#include<iostream>
#include<string>
#include<cassert>
#include "Hash.h"
#include"diff.h"
using namespace std;

#include <chrono>
#include <future>
#include <atomic>

#include <chrono>

class Timer
{
public:
	Timer()
	{
		start();
	}
	void start()
	{
		m_time = std::chrono::high_resolution_clock::now();
	}
	double elapsed() const
	{
		std::chrono::duration<double, std::milli> diff =
			std::chrono::high_resolution_clock::now() - m_time;
		return diff.count();
	}
private:
	std::chrono::high_resolution_clock::time_point m_time;
};

void testRound(string oldName, string newName) {
	ifstream oldFile(oldName, ios::binary);
	ifstream newFile(newName, ios::binary);
	ofstream diffFile("_diff.txt", ios::binary);

	cerr << oldName << ":" << endl;

	Timer t;
	createDiff(oldFile, newFile, diffFile);
	cerr << "createDiff(): \n    " << t.elapsed() << " ms" << endl;
	diffFile.close();

	ifstream diffFile2("_diff.txt", ios::binary);
	int i = 0;
	char ttt;
	while (diffFile2.get(ttt)) {
		i += 1;
	}
	cerr << "File size:" << endl;
	cerr << "    " << i << " bytes." << endl;

	oldFile.clear();   // clear the end of file condition
	oldFile.seekg(0);  // reset back to beginning of the stream

	diffFile2.clear();   // clear the end of file condition
	diffFile2.seekg(0);  // reset back to beginning of the stream

	ofstream newnew("G:/my.txt", ios::binary);

	t.start();
	if (applyDiff(oldFile, diffFile2, newnew))
		cerr << "applyDiff(): \n    " << t.elapsed() << " ms" << endl << endl;
	else
		cerr << "diff file content error\n\n";
	newnew.close();
}

void myTest() {
	while (true) {
		cerr << "Select test case \n" <<
			"---------------------------------------------------------------------------\n" <<
			"|1 smallmart | 2 greeneggs | 3 warandpeace | 4 strange | 5 other | 0 quit |\n" <<
			"---------------------------------------------------------------------------\n";
		int num = 0;
		cin >> num;
		if (num == 1)
			testRound("G:/smallmart1.txt", "G:/smallmart2.txt");
		else if (num == 2)
			testRound("G:/greeneggs1.txt", "G:/greeneggs2.txt");
		else if (num == 3)
			testRound("G:/warandpeace1.txt", "G:/warandpeace2.txt");
		else if (num == 4)
			testRound("G:/strange1.txt", "G:/strange2.txt");
		else if (num == 5) {
			int other;
			string oldName, newName;
			cerr << "Select function\n" <<
				"-------------------------------------\n" <<
				"|1 createDiff | 2 applyDiff | 3 both|\n" <<
				"-------------------------------------\n";
			cin >> other;
			cerr << "old file name: ";
			cin >> oldName;
			if (other == 1) {
				cerr << "new file name: ";
				cin >> newName;
				ifstream oldFile(oldName, ios::binary);
				ifstream newFile(newName, ios::binary);
				ofstream diffFile("G:/diff.txt", ios::binary);
				Timer t;
				createDiff(oldFile, newFile, diffFile);
				cerr << "createDiff(): \n    " << t.elapsed() << " ms" << endl;
				diffFile.close();
				ifstream diffFile2("G:/diff.txt", ios::binary);
				int i = 0;
				char ttt;
				while (diffFile2.get(ttt)) {
					i += 1;
				}
				cerr << "File size:" << endl;
				cerr << "    " << i << " bytes.\n\n";
			}
			else if (other == 2) {
				ifstream oldFile(oldName, ios::binary);
				ifstream diffFile("G:/diff.txt", ios::binary);
				ofstream newnew("G:/my.txt", ios::binary);
				Timer t;
				if (applyDiff(oldFile, diffFile, newnew))
					cerr << "applyDiff(): \n    " << t.elapsed() << " ms\n\n";
				else
					cerr << "diff file content error\n\n";
				newnew.close();
			}
			else if (other == 3) {
				cerr << "new file name: ";
				cin >> newName;
				testRound(oldName, newName);
			}
		}
		else if (num == 0)
			return;
		else
			cerr << "Invalid input." << endl;
	}
}

int main()
{
	myTest();
}