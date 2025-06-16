#include <utility>
#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"

FixedCapBiMap::FixedCapBiMap(int capacity) {
	if (capacity <= 0) {
		throw std::exception("Invalid capacity");
	}
	this->capacity = capacity;
	this->elemCounter = 0;
	this->elements = (TElem*)malloc(capacity * sizeof(TElem));
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

FixedCapBiMap::~FixedCapBiMap() {
	free(this->elements);
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

bool FixedCapBiMap::add(TKey c, TValue v) {
	if (this->isFull()) // if the map is full
		throw std::exception("Full map"); 
	ValuePair src = this->search(c); // search for the values of the key
	if (src.second != NULL_TVALUE) // if we already have 2 values for the key
		return false;
	this->elements[this->elemCounter] = std::make_pair(c, v);
	this->elemCounter++;
	return true;
}
// BC: Theta(1)
// WC: Theta(elemCounter)
// TC: O(elemCounter)

ValuePair FixedCapBiMap::search(TKey c) const {
	ValuePair vp = std::make_pair(NULL_TVALUE, NULL_TVALUE);
	for (int i = 0; i < this->elemCounter; i++) {
		if (this->elements[i].first == c) {
			if (vp.first == NULL_TVALUE) { // if we don't have the first value	
				vp.first = this->elements[i].second;
			}
			else { // if we already have the first value
				vp.second = this->elements[i].second;
				return vp;
			}
		}
	}
	// if we have only one value for the key
	return vp;
}
// BC: Theta(1)
// WC: Theta(elemCounter)
// TC: O(elemCounter)

bool FixedCapBiMap::remove(TKey c, TValue v) {
	for (int i = 0; i < this->elemCounter; i++) {
		if (this->elements[i].first == c && this->elements[i].second == v) {
			this->elements[i] = this->elements[this->elemCounter - 1];
			this->elements[this->elemCounter - 1] = NULL_TELEM;
			this->elemCounter--;
			return true;
		}
	}
	return false;
}
// BC: Theta(1)
// WC: Theta(elemCounter)
// TC: O(elemCounter)


int FixedCapBiMap::size() const {
	return this->elemCounter;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

bool FixedCapBiMap::isEmpty() const{
	return this->elemCounter == 0;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

bool FixedCapBiMap::isFull() const {
	return this->capacity == this->elemCounter;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

FixedCapBiMapIterator FixedCapBiMap::iterator() const {
	return FixedCapBiMapIterator(*this);
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

int FixedCapBiMap::countNotUniqueKeys()
{
	int count = 0;
	for (int i = 0; i < this->elemCounter; i++) {
		ValuePair vp = this->search(this->elements[i].first);
		if (vp.second != NULL_TVALUE) {
			count++;
		}
	}
	return count / 2;
}
// BC: Theta(elemCounter)
// WC: Theta(elemCounter*elemCounter)
// TC: O(elemCounter*elemCounter)