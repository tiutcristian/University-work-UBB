#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->current = this->bag.head;
	this->currentFreq = 1;
}
// BC = WC = TC = Theta(1)

void BagIterator::first() {
	this->current = this->bag.head;
	this->currentFreq = 1;
}
// BC = WC = TC = Theta(1)


void BagIterator::next() {
	if (this->current == nullptr)
		throw exception("Invalid iterator");
	if (this->currentFreq < this->current->freq)
		this->currentFreq++;
	else {
		this->current = this->current->next;
		this->currentFreq = 1;
	}
}
// BC = WC = TC = Theta(1)


void BagIterator::previous()
{
	if (this->current == nullptr)
		throw exception("Invalid iterator");
	if (this->current == this->bag.head && this->currentFreq == 1)
	{
		this->current = nullptr;
		return;
	}
	if (this->currentFreq > 1)
		this->currentFreq--;
	else {
		this->current = this->current->prev;
		this->currentFreq = this->current->freq;
	}
}
// BC = WC = TC = Theta(1)


bool BagIterator::valid() const {
	return this->current != nullptr;
}
// BC = WC = TC = Theta(1)


TElem BagIterator::getCurrent() const
{
	if (this->current == nullptr)
		throw exception("Invalid iterator");
	return this->current->info;
}
// BC = WC = TC = Theta(1)
