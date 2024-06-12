#pragma once
#include "domain.h"
#include <string>
#include <cassert>

template <typename TElement>
class DynamicVector
{
private:
	TElement* elems;
	int size;
	int capacity;

	/// <summary>
	/// Resizes the current DynamicVector, multiplying its capacity by a given factor (real number).
	/// </summary>
	/// <param name = "factor"> The factor to multiply old capacity with (by default 2) </param>
	void resize(int factor = 2)
	{
		this->capacity *= factor;

		TElement* els = new TElement[this->capacity];
		for (int i = 0; i < this->size; i++)
			els[i] = this->elems[i];

		delete[] this->elems;
		this->elems = els;
	}

public:
	/// <summary>
	/// Default constructor for a DynamicVector
	/// </summary>
	/// <param name = "capacity"> The capacity of the current DynamicVector (by default 10) </param>
	DynamicVector(int capacity = 10)
	{
		this->size = 0;
		this->capacity = capacity;
		this->elems = new TElement[capacity];
	}

	// copy constructor for a DynamicVector
	DynamicVector(const DynamicVector& v)
	{
		this->size = v.size;
		this->capacity = v.capacity;
		this->elems = new TElement[this->capacity];
		for (int i = 0; i < this->size; i++)
			this->elems[i] = v.elems[i];
	}

	// destructor for a DynamicVector
	~DynamicVector()
	{
		delete[] this->elems;
	}

	// assignment operator for a DynamicVector
	DynamicVector operator=(const DynamicVector& v)
	{
		if (this == &v)
			return *this;

		this->size = v.size;
		this->capacity = v.capacity;

		delete[] this->elems;
		this->elems = new TElement[this->capacity];
		for (int i = 0; i < this->size; i++)
			this->elems[i] = v.elems[i];

		return *this;
	}
	
	/// <summary>
	/// Overloads the subscript operator.
	/// </summary>
	/// <param name = "pos"> a valid position within the vector. </param>
	/// <returns> a reference to the element on position pos. </returns>
	inline TElement& operator[](int pos) { return this->elems[pos]; }

	// Adds an element to the current DynamicVector.
	void add(TElement e)
	{
		if (this->size == this->capacity)
			this->resize();

		this->elems[this->size++] = e;
	}

	// Deletes an element from the current DynamicVector.
	void remove(int pos)
	{
		for (int i = pos; i < this->size - 1; i++)
			this->elems[i] = this->elems[i + 1];

		this->size--;
	}

	// Returns the size of the current DynamicVector.
	inline int getSize() const { return this->size; }
};

