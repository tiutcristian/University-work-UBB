#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>
#include <cassert>

using namespace std;

bool relation(TComp e1, TComp e2) {
	return e1 <= e2;
}

void testIsSubsetOf()
{
	SortedSet s{ relation };
	SortedSet s2{ relation };
	s.add(1);
	s.add(2);
	s.add(3);
	s2.add(1);
	s2.add(3);
	s2.add(5);
	assert(s.isSubsetOf(s2) == false);
	assert(s2.isSubsetOf(s) == false);
	s2.add(2);
	assert(s.isSubsetOf(s2) == true);
}

int main() {
	testAll();
	testAllExtended();
	cout << "Testing isSubsetOf" << endl;
	testIsSubsetOf();

	cout << "Test end" << endl;
	system("pause");
}