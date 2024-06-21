#include "ExtendedTest.h"
#include "ShortTest.h"

#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"

#include <iostream>
#include <cassert>
using namespace std;

void testCountNotUniqueKeys()
{
	FixedCapBiMap b(10);
	b.add(1, 2);
	b.add(1, 3);
	b.add(2, 4);
	b.add(3, 5);
	b.add(4, 6);
	b.add(4, 7);
	b.add(5, 8);
	b.add(6, 9);
	b.add(6, 10);
	assert(b.countNotUniqueKeys() == 3);
}

void testPrevious()
{
	FixedCapBiMap b(10);
	b.add(1, 2);
	b.add(1, 3);
	b.add(2, 4);
	b.add(3, 5);
	b.add(4, 6);
	b.add(4, 7);
	b.add(5, 8);
	b.add(6, 9);
	b.add(6, 10);

	FixedCapBiMapIterator it = b.iterator();
	assert(it.valid());
	assert(it.getCurrent().first == 1);
	assert(it.getCurrent().second == 2);
	it.next();
	assert(it.valid());
	assert(it.getCurrent().first == 1);
	assert(it.getCurrent().second == 3);
	it.next();
	assert(it.valid());
	assert(it.getCurrent().first == 2);
	assert(it.getCurrent().second == 4);
	it.next();
	assert(it.valid());
	assert(it.getCurrent().first == 3);
	assert(it.getCurrent().second == 5);
	it.next();
	assert(it.valid());
	assert(it.getCurrent().first == 4);
	assert(it.getCurrent().second == 6);
	it.next();
	assert(it.valid());
	assert(it.getCurrent().first == 4);
	assert(it.getCurrent().second == 7);
	it.next();
	assert(it.valid());
	assert(it.getCurrent().first == 5);
	assert(it.getCurrent().second == 8);
	it.next();
	assert(it.valid());
	assert(it.getCurrent().first == 6);
	assert(it.getCurrent().second == 9);
	it.next();
	assert(it.valid());
	assert(it.getCurrent().first == 6);
	assert(it.getCurrent().second == 10);
	it.next();
	assert(!it.valid());
	it.previous();
	assert(it.valid());
	assert(it.getCurrent().first == 6);
	assert(it.getCurrent().second == 10);
	it.previous();
	assert(it.valid());
	assert(it.getCurrent().first == 6);
	assert(it.getCurrent().second == 9);
	it.previous();
	assert(it.valid());
	assert(it.getCurrent().first == 5);
	assert(it.getCurrent().second == 8);
	it.previous();
	assert(it.valid());
	assert(it.getCurrent().first == 4);
	assert(it.getCurrent().second == 7);
	it.previous();
	assert(it.valid());
	assert(it.getCurrent().first == 4);
	assert(it.getCurrent().second == 6);
	it.previous();
	assert(it.valid());
	assert(it.getCurrent().first == 3);
	assert(it.getCurrent().second == 5);
	it.previous();
	assert(it.valid());
	assert(it.getCurrent().first == 2);
	assert(it.getCurrent().second == 4);
}

int main() {
	testAll();
	testAllExtended();
	testCountNotUniqueKeys();
	testPrevious();

	cout << "That's all!" << endl;
	system("pause");
	return 0;
}