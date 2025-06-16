#pragma once
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef TElem TComp;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TELEM -11111
class SortedSetIterator;

/*
* ADT SortedSet 
	– using a BST with linked representation with dynamic allocation
	- Implement the given container using the given representation 
	and a binary search tree as a data structure.
	- Do not implement a separate class for the binary search tree 
	(or for the dynamic array), implement the container directly!
*/
struct BSTNode {
	TElem info;
	BSTNode* left;
	BSTNode* right;
};

class SortedSet {
	friend class SortedSetIterator;
private:
	BSTNode* root;
	Relation relation;
	int length;	

	BSTNode* insert_it(BSTNode* node, TElem e);

public:
	//constructor
	SortedSet(Relation r);

	//adds an element to the sorted set
	//if the element was added, the operation returns true, otherwise (if the element was already in the set) 
	//it returns false
	bool add(TComp e);

	
	//removes an element from the sorted set
	//if the element was removed, it returns true, otherwise false
	bool remove(TComp e);

	//checks if an element is in the sorted set
	bool search(TElem elem) const;


	//returns the number of elements from the sorted set
	int size() const;

	//checks if the sorted set is empty
	bool isEmpty() const;

	bool isSubsetOf(SortedSet& s) const;

	//returns an iterator for the sorted set
	SortedSetIterator iterator() const;

	// destructor
	~SortedSet();


};
