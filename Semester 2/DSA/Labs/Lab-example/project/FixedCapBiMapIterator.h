#pragma once
#include "FixedCapBiMap.h"
class FixedCapBiMapIterator
{
	//DO NOT CHANGE THIS PART
	friend class FixedCapBiMap;

private:
	const FixedCapBiMap& map;
	int current;
	FixedCapBiMapIterator(const FixedCapBiMap& m);

public:
	void first();
	void next();
	void previous();
	TElem getCurrent();
	bool valid() const;
	bool validBegin() const;
	bool validEnd() const;
};


