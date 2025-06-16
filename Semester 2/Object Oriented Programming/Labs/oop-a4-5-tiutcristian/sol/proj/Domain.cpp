#include "Domain.h"
#include <cassert>
using namespace std;

Coat::Coat()
{
	this->size = ' ';
	this->colour = "";
	this->price = 0;
	this->quantity = 0;
	this->photo = "";
}

Coat::Coat(char size, string colour, double price, int quantity, string photo)
{
	this->size = size;
	this->colour = colour;
	this->price = price;
	this->quantity = quantity;
	this->photo = photo;
}

string Coat::toString()
{
	string res = "";
	res += this->size;
	res += " ";
	res += this->colour;
	res += " ";
	res += to_string(this->price);
	res += " ";
	res += to_string(this->quantity);
	res += " ";
	res += this->photo;
	return res;
}

bool Coat::operator==(const Coat& c)
{
	return (this->size == c.size && this->colour == c.colour);
}

char Coat::getSize() const
{
	return this->size;
}

string Coat::getColor() const
{
	return this->colour;
}

double Coat::getPrice() const
{
	return this->price;
}

int Coat::getQuantity() const
{
	return this->quantity;
}

string Coat::getPhoto() const
{
	return this->photo;
}

void Coat::setSize(char size)
{
	this->size = size;
}

void Coat::setColour(string colour)
{
	this->colour = colour;
}

void Coat::setPrice(double price)
{
	this->price = price;
}

void Coat::setQuantity(int quantity)
{
	this->quantity = quantity;
}

void Coat::setPhoto(string photo)
{
	this->photo = photo;
}

void Coat::testCoat()
{
	Coat c{ 'M', "red", 100, 10, "photo1" };
	assert(c.getSize() == 'M');
	assert(c.getColor() == "red");
	assert(c.getPrice() == 100);
	assert(c.getQuantity() == 10);
	assert(c.getPhoto() == "photo1");

	c.setSize('S');
	c.setColour("blue");
	c.setPrice(200);
	c.setQuantity(20);
	c.setPhoto("photo2");
	assert(c.getSize() == 'S');
	assert(c.getColor() == "blue");
	assert(c.getPrice() == 200);
	assert(c.getQuantity() == 20);
	assert(c.getPhoto() == "photo2");

	Coat c2{ 'S', "blue", 200, 20, "photo2" };
	assert(c == c2);
	assert(c.toString() == "S blue 200.000000 20 photo2");

	c = c2;
	assert(c == c2);
}
