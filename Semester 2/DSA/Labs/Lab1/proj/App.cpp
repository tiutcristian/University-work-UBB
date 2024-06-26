
#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <cassert>

using namespace std;

void testSetElemsOnLine()
{
	Matrix m(3, 3);
	m.modify(0, 1, 2);
	m.modify(0, 2, 3);
	m.modify(1, 0, 4);
	m.modify(1, 2, 6);
	m.modify(2, 0, 7);
	m.modify(2, 1, 8);
	m.setElemsOnLine(1, 3);
	assert(m.element(0, 0) == NULL_TELEM);
	assert(m.element(0, 1) == 2);
	assert(m.element(0, 2) == 3);
	assert(m.element(1, 0) == 3);
	assert(m.element(1, 1) == 3);
	assert(m.element(1, 2) == 3);
	assert(m.element(2, 0) == 7);
	assert(m.element(2, 1) == 8);
	assert(m.element(2, 2) == NULL_TELEM);
}

int main() {

	testSetElemsOnLine();
	testAll();
	testAllExtended();
	cout << "Test End" << endl;
	system("pause");
}