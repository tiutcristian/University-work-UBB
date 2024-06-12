#pragma once
#include <string>
#include <iostream>
using namespace std;

class Coat
{
private:
	char size;
	string color;
	double price;
	int quantity;	
	string photo;

public:
	// Constructor without parameters
	Coat() : size(' '), color(""), price(0), quantity(0), photo("") {}

	// Constructor with parameters
	Coat(char size, string colour, double price, int quantity, string photo);

	// Returns the coat as a string
	string toString();

	// Overloading the equality operator
	bool operator==(const Coat& c);

	// Extraction and insertion operators overloading
	friend ostream & operator<<(ostream& stream, const Coat& c);
	friend istream & operator>>(istream& stream, Coat& c);

	// Getters
	char getSize() const { return size; }
	string getColor() const { return color; }
	double getPrice() const { return price; }
	int getQuantity() const { return quantity; }
	string getPhoto() const { return photo; }

	// Setters
	void setSize(char size) { this->size = size; }
	void setColour(string colour) { this->color = colour; }
	void setPrice(double price) { this->price = price; }
	void setQuantity(int quantity) { this->quantity = quantity; }
	void setPhoto(string photo) { this->photo = photo; }

	// Tests
	static void testCoat();
};
