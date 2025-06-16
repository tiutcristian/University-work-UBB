#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
using namespace std;


FixedCapBiMapIterator::FixedCapBiMapIterator(const FixedCapBiMap& d) : map(d)
{
	this->first();
}
// BC: theta(1)
// WC: theta(1)
// TC: theta(1)


void FixedCapBiMapIterator::first() {
	this->current = 0;
}
// BC: theta(1)
// WC: theta(1)
// TC: theta(1)


void FixedCapBiMapIterator::next() {
	if (!this->validEnd())
		throw exception();
	this->current++;
}
// BC: theta(1)
// WC: theta(1)
// TC: theta(1)

void FixedCapBiMapIterator::previous()
{
	if (!this->validBegin())
		throw exception();
	this->current--;
}
// BC: theta(1)
// WC: theta(1)
// TC: theta(1)

TElem FixedCapBiMapIterator::getCurrent(){
	if (!this->valid())
		throw exception();
	return this->map.elements[this->current];
}
// BC: theta(1)
// WC: theta(1)
// TC: theta(1)


bool FixedCapBiMapIterator::valid() const {
	return this->validBegin() && this->validEnd();
}
// BC: theta(1)
// WC: theta(1)
// TC: theta(1)

bool FixedCapBiMapIterator::validBegin() const
{
	return this->current >= 0;
}
// BC: theta(1)
// WC: theta(1)
// TC: theta(1)

bool FixedCapBiMapIterator::validEnd() const
{
	return this->current < this->map.elemCounter;
}
// BC: theta(1)
// WC: theta(1)
// TC: theta(1)