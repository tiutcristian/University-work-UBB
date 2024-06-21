#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	this->crtIndex = 0;
	while (this->crtIndex < this->col.m && this->col.table[this->crtIndex] == nullptr)
		this->crtIndex++;
	if (this->crtIndex < this->col.m)
		this->current = this->col.table[this->crtIndex];
	else
		this->current = nullptr;
}
// BC: theta(1)
// WC: theta(m)
// TC: O(m)

TElem MultiMapIterator::getCurrent() const{
	if (this->current == nullptr)
		throw std::exception("Invalid iterator");
	return this->current->info;
}
// BC = WC = TC: theta(1)

bool MultiMapIterator::valid() const {
	return this->current != nullptr;
}
// BC = WC = TC: theta(1)

void MultiMapIterator::next() {
	if (this->current == nullptr)
		throw std::exception("Invalid iterator");
	if (this->current->next != nullptr)
		this->current = this->current->next;
	else {
		do
		{
			this->crtIndex++;
		} while (this->crtIndex < this->col.m && this->col.table[this->crtIndex] == nullptr);
		if (this->crtIndex < this->col.m)
			this->current = this->col.table[this->crtIndex];
		else
			this->current = nullptr;
	}
}
// BC: theta(1)
// WC: theta(m)
// TC: O(m)

void MultiMapIterator::first() {
	this->crtIndex = 0;
	while(this->crtIndex < this->col.m && this->col.table[this->crtIndex] == nullptr)
		this->crtIndex++;
	if (this->crtIndex < this->col.m)
		this->current = this->col.table[this->crtIndex];
	else
		this->current = nullptr;
}
// BC: theta(1)
// WC: theta(m)
// TC: theta(m)

