#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

void SortedIndexedList::resize()
{
	TComp* newElems = new TComp[this->cap * 2];
	int* newNext = new int[this->cap * 2];
	for (int i = 0; i < this->cap; i++) {
		newElems[i] = this->elems[i];
		newNext[i] = this->next[i];
	}
	for (int i = this->cap; i < this->cap * 2 - 1; i++) {
		newNext[i] = i + 1;
	}
	newNext[this->cap * 2 - 1] = -1;
	delete[] this->elems;
	delete[] this->next;
	this->elems = newElems;
	this->next = newNext;
	this->firstEmpty = this->cap;
	this->cap *= 2;
}
// BC = WC = TC = Theta(n), where n is the capacity of the list

SortedIndexedList::SortedIndexedList(Relation r) {
	this->r = r;
	this->cap = 10;
	this->elems = new TComp[this->cap];
	this->next = new int[this->cap];
	this->length = 0;
	this->head = -1;
	this->firstEmpty = 0;
	for (int i = 0; i < this->cap - 1; i++) {
		next[i] = i + 1;
	}
	next[this->cap - 1] = -1;
}
// BC = WC = TC = Theta(n), where n is the capacity of the list

int SortedIndexedList::size() const {
	return this->length;
}
// BC = WC = TC = Theta(1)

bool SortedIndexedList::isEmpty() const {
	return this->length == 0;
}
// BC = WC = TC = Theta(1)

TComp SortedIndexedList::getElement(int i) const{
	if (i < 0 || i >= this->length) {
		throw exception("Invalid position");
	}
	int current = head;
	while (i > 0) {
		current = next[current];
		i--;
	}
	return elems[current];
}
// BC: Theta(1)
// WC: Theta(n)
// TC: O(n)

TComp SortedIndexedList::remove(int i) {
	if (i < 0 || i >= this->length) {
		throw exception("Invalid position");
	}
	int current = head;
	int left = -1;
	while (i > 0) {
		left = current;
		current = next[current];
		i--;
	}
	if (left == -1)
		head = next[current];
	else
		next[left] = next[current];
	TComp removed = elems[current];
	next[current] = firstEmpty;
	firstEmpty = current;
	length--;
	return removed;
}
// BC: Theta(1)
// WC: Theta(n)
// TC: O(n)

int SortedIndexedList::search(TComp e) const {
	int current = head;
	int pos = 0;
	while (current != -1 && elems[current] != e) {
		current = next[current];
		pos++;
	}
	return current == -1 ? -1 : pos;
}
// BC: Theta(1)
// WC: Theta(n)
// TC: O(n)

void SortedIndexedList::add(TComp e) {
	if (length == cap)
		resize();
	int left = -1;
	int right = head;
	while (right != -1 && !r(e, elems[right])) {
		left = right;
		right = next[right];
	}
	int newPos = firstEmpty;
	firstEmpty = next[firstEmpty];
	elems[newPos] = e;
	next[newPos] = right;
	if (left == -1)
		head = newPos;
	else
		next[left] = newPos;
	length++;
}
// BC: Theta(1)
// WC: Theta(n)
// TC: O(n)

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}
// BC = WC = TC = Theta(1)

//destructor
SortedIndexedList::~SortedIndexedList() {
	delete[] this->elems;
	delete[] this->next;
}
// BC = WC = TC = Theta(1)
