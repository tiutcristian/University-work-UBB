#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

void MultiMap::resizeAndRehash()
{
	int oldM = this->m;
	this->m *= 2;
	Node** newTable = new Node*[this->m];
	for (int i = 0; i < this->m; i++)
		newTable[i] = nullptr;
	for (int i = 0; i < oldM; i++) {
		Node* current = this->table[i];
		while (current != nullptr) {
			int newIndex = h(current->info.first);
			Node* newNode = new Node;
			newNode->info = current->info;
			if (newTable[newIndex] == nullptr) {
				newTable[newIndex] = newNode;
				newNode->next = nullptr;
			}
			else {
				newNode->next = newTable[newIndex];
				newTable[newIndex] = newNode;
			}
			current = current->next;
		}
	}
	for (int i = 0; i < oldM; i++) {
		Node* current = this->table[i];
		while (current != nullptr) {
			Node* next = current->next;
			delete current;
			current = next;
		}
	}
	delete[] this->table;
	this->table = newTable;
}
// BC: Theta(m)
// WC: Theta(m+length)
// TC: O(m+lenght)
// Amortized and on average: Theta(m)

MultiMap::MultiMap() {
	this->m = 10;
	this->length = 0;
	this->table = new Node*[m];
	for (int i = 0; i < m; i++)
		this->table[i] = nullptr;
}
// BC = WC = TC = Theta(m)


void MultiMap::add(TKey c, TValue v) {
	if (this->length >= 0.7 * this->m)
		resizeAndRehash();
	int i = h(c);
	Node* newNode = new Node;
	newNode->info = make_pair(c, v);
	if (this->table[i] == nullptr) {
		this->table[i] = newNode;
		newNode->next = nullptr;
	}
	else {
		newNode->next = this->table[i];
		this->table[i] = newNode;
	}
	this->length++;
}
// BC = Theta(1)
// WC = Theta(m+length)
// TC = O(m+length)
// Amortized and on average: Theta(1)


bool MultiMap::remove(TKey c, TValue v) {
	int i = h(c);
	Node* current = this->table[i];
	Node* previous = nullptr;
	while (current != nullptr) {
		if (current->info.first == c && current->info.second == v) {
			if (previous == nullptr)
				this->table[i] = current->next;
			else
				previous->next = current->next;
			delete current;
			this->length--;
			return true;
		}
		previous = current;
		current = current->next;
	}
	return false;
}
// BC = Theta(1)
// WC = Theta(length)
// TC = O(length)
// Amortized and on average: Theta(1)

vector<TValue> MultiMap::search(TKey c) const {
	int i = h(c);
	Node* current = this->table[i];
	vector<TValue> values;
	while (current != nullptr) {
		if (current->info.first == c)
			values.push_back(current->info.second);
		current = current->next;
	}
	return values;
}
// BC = Theta(1)
// WC = Theta(length)
// TC = O(length)
// Amortized and on average: Theta(1)

int MultiMap::size() const {
	return this->length;
}
// BC = WC = TC = Theta(1)


bool MultiMap::isEmpty() const {
	return this->length == 0;
}
// BC = WC = TC = Theta(1)

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}
// BC = WC = TC = Theta(1)

std::vector<TValue> MultiMap::removeKey(TKey key)
{
	std::vector<TValue> values;
	int i = h(key);
	Node* current = this->table[i];
	Node* previous = nullptr;
	while (current != nullptr) {
		if (current->info.first == key) {
			if (previous == nullptr)
				this->table[i] = current->next;
			else
				previous->next = current->next;

			values.push_back(current->info.second);

			Node* next = current->next;
			delete current;
			current = next;
			this->length--;
		}
		else {
			previous = current;
			current = current->next;
		}
	}
	return values;
}
// BC = Theta(1)
// WC = Theta(length)
// TC = O(length)
// Amortized and on average: Theta(1)

MultiMap::~MultiMap() {
	for (int i = 0; i < m; i++) {
		Node* current = this->table[i];
		while (current != nullptr) {
			Node* next = current->next;
			delete current;
			current = next;
		}
	}
	delete[] this->table;
}
// BC = Theta(m)
// WC = Theta(m+length)
// TC = O(m+length)
// Amortized and on average: Theta(m)
