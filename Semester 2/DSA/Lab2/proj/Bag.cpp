#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	this->head = nullptr;
	this->tail = nullptr;
	this->length = 0;
}
// BC = WC = TC = Theta(1)


void Bag::add(TElem elem) {
	this->length++;
	// Check if the bag is empty
	if (this->head == nullptr) {
		DLLNode* newNode = new DLLNode;
		newNode->info = elem;
		newNode->freq = 1;
		newNode->next = nullptr;
		newNode->prev = nullptr;
		this->head = newNode;
		this->tail = newNode;
		return;
	}

	// Search for the element in the bag
	DLLNode* currentNode = this->head;
	while (currentNode != nullptr) {
		if (currentNode->info == elem) {
			currentNode->freq++;
			return;
		}
		currentNode = currentNode->next;
	}

	// Element not found, add a new node
	DLLNode* newNode = new DLLNode;
	newNode->info = elem;
	newNode->freq = 1;
	newNode->next = nullptr;
	newNode->prev = this->tail;
	this->tail->next = newNode;
	this->tail = newNode;
}
// BC = Theta(1) - we add on the first position
// WC = Theta(n) - element is not in the bag
// TC = O(n)



bool Bag::remove(TElem elem) {
	DLLNode* currentNode = this->head;
	while (currentNode != nullptr && currentNode->info != elem)
		currentNode = currentNode->next;
	if (currentNode == nullptr)
		return false;
	this->length--;
	if (currentNode->freq > 1)
		currentNode->freq--;
	else {
		if (currentNode->prev != nullptr)
			currentNode->prev->next = currentNode->next;
		else
			this->head = currentNode->next;
		if (currentNode->next != nullptr)
			currentNode->next->prev = currentNode->prev;
		else
			this->tail = currentNode->prev;
		delete currentNode;
	}
	return true;
}
// BC = Theta(1) - element is the first in the bag
// WC = Theta(n) - element is not in the bag
// TC = O(n)


bool Bag::search(TElem elem) const {
	DLLNode* currentNode = this->head;
	while (currentNode != nullptr && currentNode->info != elem)
		currentNode = currentNode->next;
	return currentNode != nullptr;
}
// BC = Theta(1) - element is the first in the bag
// WC = Theta(n) - element is not in the bag
// TC = O(n)


int Bag::nrOccurrences(TElem elem) const {
	DLLNode* currentNode = this->head;
	while (currentNode != nullptr && currentNode->info != elem)
		currentNode = currentNode->next;
	return (currentNode == nullptr) ? 0 : currentNode->freq;
}
// BC = Theta(1) - element is the first in the bag
// WC = Theta(n) - element is not in the bag
// TC = O(n)


int Bag::size() const {
	return this->length;
}
// BC = WC = TC = Theta(1)


bool Bag::isEmpty() const {
	return this->length == 0;
}
// BC = WC = TC = Theta(1)

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}
// BC = WC = TC = Theta(1)


Bag::~Bag() {
	DLLNode* currentNode = this->head;
	while (currentNode != nullptr) {
		DLLNode* nextNode = currentNode->next;
		delete currentNode;
		currentNode = nextNode;
	}
}
// BC = WC = TC = Theta(n)
