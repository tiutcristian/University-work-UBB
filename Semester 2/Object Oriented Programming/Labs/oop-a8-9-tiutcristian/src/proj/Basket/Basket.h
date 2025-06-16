#pragma once
#include <vector>
#include "../Domain/Domain.h"

class Basket
{
protected:
	std::vector<Coat> shoppingBasket;

	int findCoat(char size, const std::string& color);

public:
	Basket() {}

	inline Coat& operator[](int pos) { return this->shoppingBasket[pos]; }

	int getSize() const { return (int)this->shoppingBasket.size(); }

	void addCoat(const Coat& coat);

	std::string toString();

	static void testBasket();
};