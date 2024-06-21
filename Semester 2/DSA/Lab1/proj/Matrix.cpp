#include "Matrix.h"
#include <exception>
using namespace std;


void Matrix::resizeUp()
{
	this->capacity *= 2;
	Triple* newElements = new Triple[this->capacity];
	for (int i = 0; i < this->length; i++)
		newElements[i] = this->elements[i];
	delete[] this->elements;
	this->elements = newElements;
}
// BC = WC = TC: Theta(length)

void Matrix::resizeDown()
{
	this->capacity /= 2;
	Triple* newElements = new Triple[this->capacity];
	for (int i = 0; i < this->length; i++)
		newElements[i] = this->elements[i];
	delete[] this->elements;
	this->elements = newElements;
}
// BC = WC = TC: Theta(length)

void Matrix::addElement(int pos, int line, int column, TElem value)
{
	if (this->length == this->capacity)
		this->resizeUp();
	for (int i = this->length; i > pos; i--)
		this->elements[i] = this->elements[i - 1];
	this->elements[pos].line = line;
	this->elements[pos].column = column;
	this->elements[pos].value = value;
	this->length++;
}
// BC: Theta(1)
// WC: Theta(length)
// TC: O(length)

TElem Matrix::removeElement(int pos)
{
	TElem oldValue = this->elements[pos].value;
	for (int i = pos; i < this->length - 1; i++)
		this->elements[i] = this->elements[i + 1];
	this->length--;
	if (this->length < this->capacity / 4)
		this->resizeDown();
	return oldValue;
}
// BC: Theta(1)
// WC: Theta(length)
// TC: O(length)

TElem Matrix::updateElement(int pos, TElem value)
{
	TElem oldValue = this->elements[pos].value;
	this->elements[pos].value = value;
	return oldValue;
}
// BC = WC = TC: Theta(1)

int Matrix::searchPos(int line, int column) const
{
	int left = 0, right = this->length - 1;
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (this->elements[mid].line == line && this->elements[mid].column == column)
			return mid;
		if (this->elements[mid].line < line || (this->elements[mid].line == line && this->elements[mid].column < column))
			left = mid + 1;
		else
			right = mid - 1;
	}
	return left;
}
// BC: Theta(1)
// WC: Theta(log(length))
// TC: O(log(length))

Matrix::Matrix(int nrLines, int nrCols) {
	   
	this->noLines = nrLines;
	this->noCols = nrCols;
	this->capacity = INITIAL_CAPACITY;
	this->length = 0;
	this->elements = new Triple[INITIAL_CAPACITY];
}
// BC = WC = TC: Theta(1)

Matrix::~Matrix()
{
	delete[] this->elements;
}
// BC = WC = TC: Theta(1)

int Matrix::nrLines() const {
	return this->noLines;
}
// BC = WC = TC: Theta(1)

int Matrix::nrColumns() const {
	return this->noCols;
}
// BC = WC = TC: Theta(1)

TElem Matrix::element(int i, int j) const {
	if (i < 0 || i >= this->noLines || j < 0 || j >= this->noCols)
		throw exception("Invalid position");
	int k = this->searchPos(i, j);
	if (this->elements[k].line == i && this->elements[k].column == j)
		return this->elements[k].value;
	return NULL_TELEM;
}
// BC: Theta(1)
// WC: Theta(log(length))
// TC: O(log(length))

TElem Matrix::modify(int i, int j, TElem e) 
{
	// if parameters are invalid, throw exception
	if (i < 0 || i >= this->noLines || j < 0 || j >= this->noCols)
		throw exception("Invalid position");

	// search for the position of the element and check if a non-null element was found
	int pos = this->searchPos(i, j);
	bool found = (this->elements[pos].line == i && this->elements[pos].column == j);

	if (e == NULL_TELEM)
	{
		// if the new element is NULL_TELEM and the position was found, remove it
		if (found)
			return this->removeElement(pos);
		
		// if the new element is NULL_TELEM and the position was not found, nothing changes
		return NULL_TELEM;
	}

	// if the element is not NULL_TELEM, but it was found, modify it
	if (found)
		return this->updateElement(pos, e);

	// if the element is not NULL_TELEM and it was not found, add it
	this->addElement(pos, i, j, e);
	return NULL_TELEM;
}
// BC: Theta(1)
// WC: Theta(length)
// TC: O(length)

void Matrix::setElemsOnLine(int line, TElem elem)
{
	if (line < 0 || line >= this->noLines)
		throw exception("Invalid line");
	for (int j = 0; j < this->noCols; j++)
		this->modify(line, j, elem);
}
// BC: Theta(nrCols)
// WC: Theta(nrCols*length)
// TC: O(nrCols*length)