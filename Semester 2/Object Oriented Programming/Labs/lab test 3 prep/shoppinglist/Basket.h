#pragma once
#include <Item.h>
#include <vector>

class Basket
{
private:
	std::vector<Item> items;

	void readFromFile();
public:
	Basket();
	std::vector<std::string> getItems();
	std::vector<std::string> getItemsByCategory(const std::string& category);
};

