#include "SortedSet.h"
#include "SortedSetIterator.h"

BSTNode* SortedSet::insert_it(BSTNode* node, TElem e)
{
	BSTNode* newNode = new BSTNode;
	newNode->info = e;
	newNode->left = nullptr;
	newNode->right = nullptr;

	if (root == nullptr) {
		root = newNode;
		return root;
	}

	BSTNode* current = root;
	BSTNode* parent = nullptr;

	while (current) {
		parent = current;
		if (relation(e, current->info))
			current = current->left;
		else
			current = current->right;
	}

	if (relation(e, parent->info)) 
		parent->left = newNode;
	else 
		parent->right = newNode;

	return root;
}
// BC: Theta(1)
// WC: Theta(height)
// TC: O(height)
// height between log2(n) and n

SortedSet::SortedSet(Relation r) {
	this->relation = r;
	this->root = nullptr;
	this->length = 0;
}
// BC = WC = TC = Theta(1)


bool SortedSet::add(TComp elem) {
	if (search(elem))
		return false;
	root = insert_it(root, elem);
	this->length++;
	return true;
}
// BC: Theta(1)
// WC: Theta(height)
// TC: O(height)
// height between log2(n) and n


bool SortedSet::remove(TComp elem) {
	BSTNode* current = root;
	BSTNode* parent = nullptr;
	while (current != nullptr) {
		if (current->info == elem)
			break;
		else if (relation(current->info, elem)) {
			parent = current;
			current = current->right;
		} else {
			parent = current;
			current = current->left;
		}
	}
	if (current == nullptr)
		return false;

	// Case 1: no descendants
	if (current->left == nullptr && current->right == nullptr) {
		if (parent == nullptr) // the node is the root
			root = nullptr;
		else if (parent->left == current)
			parent->left = nullptr;
		else
			parent->right = nullptr;
		delete current;
	}
	// Case 2: only right descendant
	else if (current->left == nullptr) {
		if (parent == nullptr)
			root = current->right;
		else if (parent->left == current)
			parent->left = current->right;
		else
			parent->right = current->right;
		delete current;
	}
	// Case 3: only left descendant
	else if (current->right == nullptr) {
		if (parent == nullptr)
			root = current->left;
		else if (parent->left == current)
			parent->left = current->left;
		else
			parent->right = current->left;
		delete current;
	}
	// Case 4: both descendants
	else {
		BSTNode* successor = current->right;
		while (successor->left != nullptr)
			successor = successor->left;
		TComp aux = successor->info;
		remove(successor->info);
		current->info = aux;
	}
	this->length--;
	return true;
}
// BC: Theta(1)
// WC: Theta(height)
// TC: O(height)
// height between log2(n) and n


bool SortedSet::search(TElem elem) const {
	BSTNode* current = root;
	while (current != nullptr) {
		if (current->info == elem)
			return true;
		if (relation(current->info, elem))
			current = current->right;
		else
			current = current->left;
	}
	return false;
}
// BC: Theta(1)
// WC: Theta(height)
// TC: O(height)
// height between log2(n) and n


int SortedSet::size() const {
	return this->length;
}
// BC = WC = TC = Theta(1)


bool SortedSet::isEmpty() const {
	return this->length == 0;
}
// BC = WC = TC = Theta(1)

bool SortedSet::isSubsetOf(SortedSet& s) const
{
	SortedSetIterator it = this->iterator();
	while (it.valid()) {
		if (!s.search(it.getCurrent()))
			return false;
		it.next();
	}
	return true;
}
// BC: Theta(n)
// WC: Theta(n*m)
// TC: O(n*m)

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}
// BC = WC = TC = Theta(n)


SortedSet::~SortedSet() {
	if (root == nullptr)
		return;
	BSTNode** stack = new BSTNode*[this->length];
	int stackSize = 0;
	stack[stackSize++] = root;
	while (stackSize > 0) {
		BSTNode* current = stack[--stackSize];
		if (current->left != nullptr)
			stack[stackSize++] = current->left;
		if (current->right != nullptr)
			stack[stackSize++] = current->right;
		delete current;
	}
	delete[] stack;
}
// BC = WC = TC = Theta(n)
