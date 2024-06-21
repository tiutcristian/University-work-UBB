#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

#include "SortedIndexedList.h"
#include "ListIterator.h"
#include <assert.h>

using namespace std;

bool relation(TComp e1, TComp e2) {
	return e1 <= e2;
}

void testJumpForward() {
	cout << "Test jump forward\n";
	SortedIndexedList list{relation};
	list.add(1);
	list.add(2);
	list.add(3);
	list.add(4);
	list.add(5);
	ListIterator it = list.iterator();
	it.jumpForward(2);
	assert(it.getCurrent() == 3);
	it.jumpForward(2);
	assert(it.getCurrent() == 5);
	it.jumpForward(2);
	assert(it.valid() == false);
	try
	{
		it.jumpForward(2);
		assert(false);
	}
	catch (const std::exception&)
	{
		assert(true);
	}
}

int main(){
    testAll();
    testAllExtended();
	testJumpForward();
    std::cout<<"Finished IL Tests!"<<std::endl;
	system("pause");
}