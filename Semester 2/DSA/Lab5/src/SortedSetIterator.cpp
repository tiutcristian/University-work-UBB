#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	elements = new TElem[multime.size()];
	inOrder();
	position = 0;
}
// WC = BC = TC = Theta(n)

SortedSetIterator::~SortedSetIterator()
{
	delete[] this->elements;
}
// WC = BC = TC = Theta(1)


void SortedSetIterator::inOrder()
{
	BSTNode** st = new BSTNode* [multime.size()];
	int stSize = 0;
	int cnt = 0;
	BSTNode* currentNode = multime.root;
	while(currentNode != nullptr)
	{
		st[stSize++] = currentNode;
		currentNode = currentNode->left;
	}
	while(stSize > 0)
	{
		currentNode = st[--stSize];
		elements[cnt++] = currentNode->info;
		currentNode = currentNode->right;
		while(currentNode != nullptr)
		{
			st[stSize++] = currentNode;
			currentNode = currentNode->left;
		}
	}
	delete[] st;
}
// WC = BC = TC = Theta(n)

void SortedSetIterator::first() {
	position = 0;
}
// WC = BC = TC = Theta(1)


void SortedSetIterator::next() {
	if (!valid())
		throw exception();
	position++;
}
// WC = BC = TC = Theta(1)


TElem SortedSetIterator::getCurrent()
{
	if (!valid())
		throw exception();
	return elements[position];
}
// WC = BC = TC = Theta(1)

bool SortedSetIterator::valid() const {
	return position < multime.size();
}
// WC = BC = TC = Theta(1)

