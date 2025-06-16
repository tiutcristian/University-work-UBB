#pragma once
#include "Repository.h"
#include <string>
using namespace std;

class Services
{
private:
	Repository& repo;

public:
	// Default constructor for a Service.
	Services(Repository& repo) : repo{ repo } {}

	// Copy constructor for a Service.
	Services(const Services& s) : repo{ s.repo } {}

	void initializeServ();

	// Adds a new element to the repository.
	bool add(char size, string color, double price, int quantity, string photo);
	
	// Removes an element from the repository.
	bool remove(char size, string color);
	
	// Updates an element from the repository.
	bool update(char size, string color, double newPrice, int newQuantity, string newPhoto);

	// Decrement the quantity of an element from the repository.
	void decrementQuantity(char size, string color) { this->repo.decrementQuantity(size, color); }
	
	// Returns the elements from the repository as a string.
	string getElementsAsString();

	// Returns the repository filtered by size.
	Repository filterBySize(char size) { return this->repo.filterBySize(size); }
	
	// Tests
	static void testService();
};
