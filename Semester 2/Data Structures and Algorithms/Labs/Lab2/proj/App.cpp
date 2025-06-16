#include "Bag.h"
#include "BagIterator.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>
#include <chrono>
#include <cassert>

using namespace std;

void testPrevious()
{
	Bag b;
	b.add(1);
	b.add(2);
	b.add(3);
	BagIterator it = b.iterator();
	it.first();
	it.next();
	it.next();
	it.next();
	assert(it.valid() == false);
	it.first();
	it.next();
	it.next();
	assert(it.valid() == true);
	assert(it.getCurrent() == 3);
	it.previous();
	assert(it.valid() == true);
	assert(it.getCurrent() == 2);
	it.previous();
	assert(it.valid() == true);
	assert(it.getCurrent() == 1);
	it.previous();
	assert(it.valid() == false);
}

int main() {

	testAll();
	cout << "Short tests over" << endl;

	//auto start = std::chrono::high_resolution_clock::now();
	testAllExtended();
	//auto end = std::chrono::high_resolution_clock::now();
	//std::chrono::duration<double> elapsed_seconds = end - start;
	//cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
	cout << "All test over" << endl;

	testPrevious();
	cout << "Previous test over" << endl;
}