#pragma once
#include <string>
#include "../Repository/Repository.h"
#include "../Domain/DomainValidator.h"
#include "../Basket/FileBasket.h"

using namespace std;

class Action
{
public:
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
	virtual ~Action() = default;
};

class ActionAdd : public Action
{
private:
	Repository& repo;
	Coat coat;
public:
	ActionAdd(Repository& repo, const Coat& coat) : repo{ repo }, coat{ coat } {}
	void executeUndo() override { repo.deleteCoat(coat); }
	void executeRedo() override { repo.addCoat(coat); }
};

class ActionRemove : public Action
{
private:
	Repository& repo;
	Coat coat;
public:
	ActionRemove(Repository& repo, const Coat& coat) : repo{ repo }, coat{ coat } {}
	void executeUndo() override { repo.addCoat(coat); }
	void executeRedo() override { repo.deleteCoat(coat); }
};

class ActionUpdate : public Action
{
private:
	Repository& repo;
	Coat oldCoat;
	Coat newCoat;
public:
	ActionUpdate(Repository& repo, const Coat& oldCoat, const Coat& newCoat) : repo{ repo }, oldCoat{ oldCoat }, newCoat{ newCoat } {}
	void executeUndo() override { repo.updateCoat(newCoat, oldCoat); }
	void executeRedo() override { repo.updateCoat(oldCoat, newCoat); }
};

class Services
{
private:
	Repository& repo;
	DomainValidator validator;
	std::vector<std::unique_ptr<Action>> undoActions;
	std::vector<std::unique_ptr<Action>> redoActions;

public:
	// Default constructor for a Service.
	Services(Repository& repo) : repo{ repo } {}

	// Copy constructor for a Service.
	Services(const Services& s) : repo{ s.repo } {}

	void initializeServ();

	// Adds a new element to the repository.
	void add(char size, string color, double price, int quantity, string photo);
	
	// Removes an element from the repository.
	void remove(char size, string color);
	
	// Updates an element from the repository.
	void update(char size, string color, double newPrice, int newQuantity, string newPhoto);

	// Decrement the quantity of an element from the repository.
	void decrementQuantity(char size, string color) { this->repo.decrementQuantity(size, color); }
	
	// Returns the elements from the repository as a string.
	string getElementsAsString();

	// Returns the elements from the repository in a vector.
	vector<Coat> getElements() { return this->repo.getElements(); }

	// Returns the repository filtered by size.
	Repository filterBySize(char size) { return this->repo.filterBySize(size); }

	int getQuantityBySize(char size) { return this->repo.getQuantityBySize(size); }

	void undo();

	void redo();
	
	// Tests
	static void testService();
};
