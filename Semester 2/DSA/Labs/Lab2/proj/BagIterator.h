#include "Bag.h"

class BagIterator
{
	//DO NOT CHANGE THIS PART
	friend class Bag;
	
private:
	const Bag& bag;
	//TODO  - Representation
	DLLNode* current;
	int currentFreq;

	BagIterator(const Bag& c);
public:
	void first();
	void next();
	void previous();
	TElem getCurrent() const;
	bool valid() const;
};
