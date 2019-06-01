#include <iostream>
#include <string>
#include<cassert>
using namespace std;

bool somePredicate(string s);
bool somePredicate(string s)
{
	return s.empty();
}

// Return false if the somePredicate function returns false for at
	// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
	if (n <= 0)
	{
		return true;
	}
	
	if (n > 1)
	{
		return (allTrue(a + 1, n - 1) && allTrue(a,1));
	}
	return somePredicate(a[0]);



}

// Return the number of elements in the array for which the
	// somePredicate function returns false.
int countFalse(const string a[], int n)
{
	if (n <= 0)
	{
		return 0;
	}
	if (n > 1)
	{
		
		return countFalse(a + 1, n - 1)+countFalse(a,1);
	}
	else
	{
		if (somePredicate(a[0]))
			return 0;
		else
			return 1;
	}
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const string a[], int n)
{
	if (n <= 0)
		return -1;
	if (n > 1)
	{
		int mid = n / 2;
		if (firstFalse(a,mid) != -1)
		{
			return firstFalse(a, mid);
		}
		else if (firstFalse(a+mid, n-mid) != -1)
		{
			return firstFalse(a + mid, n - mid) + mid;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		if (somePredicate(a[0]))
			return -1;
		else
			return 0;
	}
}

// Return the subscript of the least string in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int indexOfLeast(const string a[], int n)
{
	if (n <= 0)
	{
		return -1;
	}
	if (n > 1)
	{
		int mid = n / 2;
		if (a[indexOfLeast(a, mid)] <= a[indexOfLeast(a + mid, n - mid)+ mid] )
		{
			return indexOfLeast(a, mid);
		}
		else
		{
			return indexOfLeast(a + mid, n - mid) + mid;
		}
	}
	else
	{
		return 0;
	}
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool includes(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < n2)
	{
		return false;
	}
	if (n2 <= 0)
	{
		return true;
	}
	if (n1 > 0 && n2 > 0)
	{
		if (a1[0] != a2[0])
		{
			return includes(a1 + 1, n1 - 1, a2, n2);
		}
		else
		{
			return includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
		}
	}
	else
		return false;
	
}


int main()
{
	/*
	int size;
	cin >> size;
	string * a = new string[size];
	for (int i = 0; i < size; i++)
	{
		a[i] = "";
	}
	if (size >= 7)
	{
		for (int i = 0; i < 7; i++)
		{
			int position;
			cin >> position;
			a[i] = to_string(position);
		}
	}

	string b[6] = { "1","2","3","4","5","6"};
	string c[1] = { "" };


	cout << allTrue(a, size) << endl;
	cout << countFalse(a, size) << endl;
	cout << firstFalse(a, size) << endl;
	cout << indexOfLeast(a, size) << endl;
	cout << includes(a, size, b, 6) << endl;
	cout << includes(b, 6, c, 0) << endl;
	*/

	string a[] = { "","","","",""};
	string b[] = { "1", "2", "3" };
	string c[] = { "2", "1", "3","1", "2", "3","" };
	
	// test all true
	assert(allTrue(a, -1));
	assert(allTrue(a, 0));
	assert(allTrue(a, 3));
	assert(allTrue(b, 0));
	assert(!allTrue(b, 1));
	assert(allTrue(b, -1));
	assert(!allTrue(b, 3));

	// test countFalse
	assert(countFalse(a, -1) == 0);
	assert(countFalse(a, 0) == 0);
	assert(countFalse(a, 3) == 0);
	assert(countFalse(b, -1) == 0);
	for (int i = 0; i < 4; i++)
	{
		assert(countFalse(b, i) == i);
	}
	for (int i = 0; i < 7; i++)
	{
		assert(countFalse(c, i) == i);
	}
	assert(countFalse(c, 7) == 6);

	for (int i = 0; i < 4; i++)
	{
		assert(firstFalse(a, i) == -1);
	}
	for (int i = 1; i < 4; i++)
	{
		assert(firstFalse(b, i) == 0);
	}
	assert(firstFalse(b, 0) == -1);
	for (int i = 1; i < 8; i++)
	{
		assert(firstFalse(c, i) == 0);
	}
	assert(firstFalse(c, 0) == -1);

	//test index of least
	assert(indexOfLeast(a, 0) == -1);
	assert(indexOfLeast(b, 0) == -1);
	assert(indexOfLeast(c, 0) == -1);
	assert(indexOfLeast(a, -1) == -1);
	assert(indexOfLeast(b, -1) == -1);
	assert(indexOfLeast(c, -1) == -1);
	for (int i = 1; i < 4; i++)
	{
		assert(indexOfLeast(b, i) == 0);
	}
	for (int i = 2; i < 7; i++)
	{
		assert(indexOfLeast(c, i) == 1);
	}
	assert(indexOfLeast(c, 1) == 0);
	assert(indexOfLeast(c, 7) == 6);

	assert(includes(a, 0, b, 0));
	assert(includes(c, 7, a, 1));
	for (int i = 0; i < 6; i++)
	{
		assert(!includes(c, i,b,3));
	}
	assert(includes(c, 6, b, 3));
	for (int i = 2; i < 8; i++)
	{
		assert(includes(c, i, b, 1));
	}

}
