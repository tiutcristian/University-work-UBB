#pragma once
#include <string>

class Item
{
private:
	std::string category;
	std::string name;
	int quantity;
public:
	Item(std::string category, std::string name, int quantity)
		: category(category), name(name), quantity(quantity) {}
	std::string getCategory() { return category; }
	std::string getName() { return name; }
	int getQuantity() { return quantity; }
	void setCategory(std::string category) { this->category = category; }
	void setName(std::string name) { this->name = name; }
	void setQuantity(int quantity) { this->quantity = quantity; }
	std::string toString() const { return category + " | " + name + " | " + std::to_string(quantity); }
};

