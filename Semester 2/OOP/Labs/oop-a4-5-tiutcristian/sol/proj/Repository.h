#pragma once
#include "DynamicVector.h"

class Repository
{
private:
	DynamicVector<Coat> coats;

public:
	Repository() {}

	Repository(const Repository& repository);

	inline Coat& operator[](int pos) { return this->coats[pos]; }

	int getSize() const { return this->coats.getSize(); }

	bool addCoat(char size, const std::string& color, double price, int quantity, const std::string& photo);

	bool updateCoat(char size, const std::string& color, double newPrice, int newQuantity, const std::string& newPhoto);

	bool deleteCoat(char size, const std::string& color);

	int findCoat(char size, const std::string& color);

	Repository filterBySize(char size);

	void decrementQuantity(char size, const std::string& color);

	std::string toString();

	static void testRepository();
};

class Basket
{
private:
	DynamicVector<Coat> coats;

	int findCoat(char size, const std::string& color);

public:
	Basket() {}

	inline Coat& operator[](int pos) { return this->coats[pos]; }

	int getSize() const { return this->coats.getSize(); }

	void addCoat(const Coat& coat);

	std::string toString();

	static void testBasket();
};

