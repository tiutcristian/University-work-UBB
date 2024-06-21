#include <iostream>
#include "MultiMap.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "MultiMapIterator.h"
#include <cassert>

using namespace std;

void testRemoveKey() {
	cout << "Test remove key" << endl;
	MultiMap m;
	m.add(1, 10);
	m.add(1, 11);
	m.add(2, 12);
	m.add(2, 13);
	m.add(2, 14);
	m.add(2, 15);
	m.add(3, 300);
	m.add(3, 301);
	std::vector<TValue> v = m.removeKey(2);
	assert(v.size() == 4);
	assert(v[0] == 12);
	assert(v[1] == 13);
	assert(v[2] == 14);
	assert(v[3] == 15);
}

int main() {

	testRemoveKey();
	testAll();
	testAllExtended();
	cout << "End" << endl;
	system("pause");

}
