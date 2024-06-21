#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	current = list.head;
}
// BC = WC = TC = Theta(1)

void ListIterator::first(){
	current = list.head;
}
// BC = WC = TC = Theta(1)

void ListIterator::next(){
	if (current == -1) {
		throw exception("Invalid position");
	}
	current = list.next[current];
}
// BC = WC = TC = Theta(1)

bool ListIterator::valid() const{
	return current != -1;
}
// BC = WC = TC = Theta(1)

TComp ListIterator::getCurrent() const{
	if (current == -1) {
		throw exception("Invalid position");
	}
	return list.elems[current];
}
// BC = WC = TC = Theta(1)

void ListIterator::jumpForward(int k)
{
	if (k <= 0 || !valid()) {
		throw exception("Invalid number");
	}
	for (int i = 0; i < k && current != -1; i++) {
		current = list.next[current];
	}
}
// BC: Theta(1)
// WC: Theta(k)
// TC: O(k)
