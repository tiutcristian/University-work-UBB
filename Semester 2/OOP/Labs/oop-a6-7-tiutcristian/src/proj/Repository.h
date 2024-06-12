#pragma once
#include <vector>
#include "Domain.h"

class Repository
{
private:
	std::vector<Coat> coats;
	void saveToFile();
	void loadFromFile();
	std::string filename;

public:
	Repository(const std::string& filename = "tmp.txt");

	Repository(const Repository& repository) : coats(repository.coats) {}

	inline Coat& operator[](int pos) { return this->coats[pos]; }

	int getSize() const { return this->coats.size(); }

	void addCoat(const Coat& c);

	void updateCoat(const Coat& oldCoat, const Coat& newCoat);

	void deleteCoat(const Coat& c);

	std::vector<Coat>::iterator findCoatIt(char size, const std::string& color);

	Coat* findCoatPtr(char size, const std::string& color) { return &*this->findCoatIt(size, color); }

	Coat findCoat(char size, const std::string& color) { return *this->findCoatPtr(size, color); }

	Repository filterBySize(char size);

	void decrementQuantity(char size, const std::string& color);

	std::string toString();

	static void testRepository();
	
	void clearRepo() { this->coats.clear(); }

	~Repository();
};

class Basket
{
protected:
	std::vector<Coat> shoppingBasket;

	int findCoat(char size, const std::string& color);

public:
	Basket() {}

	inline Coat& operator[](int pos) { return this->shoppingBasket[pos]; }

	int getSize() const { return this->shoppingBasket.size(); }

	void addCoat(const Coat& coat);

	std::string toString();

	static void testBasket();
};

