#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& multime;
	SortedSetIterator(const SortedSet& m);

	TElem* elements;
	int position;

	void inOrder();

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
	~SortedSetIterator();
};

