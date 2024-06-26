#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0
#define INITIAL_CAPACITY 1
typedef struct {
	int line;
	int column;
	TElem value;
} Triple;

class Matrix {

private:
	/*
	* ADT Matrix – represented as a sparse matrix, 
	* using a dynamic array of triples <line, column, value> (value != 0), 
	* ordered lexicographically considering the <line, column> of every element.
	*/
	int noLines, noCols;
	int length;
	int capacity;
	Triple* elements;

	void resizeUp();
	void resizeDown();
	void addElement(int pos, int line, int column, TElem value);
	TElem removeElement(int pos);
	TElem updateElement(int pos, TElem value);
	int searchPos(int line, int column) const;

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//destructor
	~Matrix();

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	// sets all the values from line to the value elem
	// throws an exception if line is not valid
	void setElemsOnLine(int line, TElem elem);
};
