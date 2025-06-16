#include "Basket.h"
#include <fstream>
#include <algorithm>

void Basket::readFromFile()
{
	std::ifstream fin("items.txt");
	char line[200];
	while (fin.getline(line, 200))
	{
		std::string category = strtok(line, "|");
		std::string name = strtok(NULL, "|");
		int quantity = atoi(strtok(NULL, "|"));
		Item item(category, name, quantity);
		items.push_back(item);
	}
	std::sort(items.begin(), items.end(), [](Item& a, Item& b) { 
		return a.toString() < b.toString(); 
	});
	fin.close();
}

Basket::Basket()
{
	readFromFile();
}

std::vector<std::string> Basket::getItems()
{
	std::vector<std::string> itemsStr;
	for (const Item& item : items)
	{
		itemsStr.push_back(item.toString());
	}
	return itemsStr;
}

std::vector<std::string> Basket::getItemsByCategory(const std::string& category)
{
	std::vector<Item> filteredItems;
	for (auto item : items)
	{
		if (item.getCategory() == category)
		{
			filteredItems.push_back(item);
		}
	}
	std::sort(filteredItems.begin(), filteredItems.end(), [](Item& a, Item& b) {
		return a.getQuantity() < b.getQuantity();
	});
	std::vector<std::string> itemsStr;
	for (const Item& item : filteredItems)
	{
		itemsStr.push_back(item.toString());
	}
	return itemsStr;
}
