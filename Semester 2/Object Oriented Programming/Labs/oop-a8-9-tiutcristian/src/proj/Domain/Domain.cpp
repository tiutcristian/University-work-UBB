#include "Domain.h"
#include <cassert>

using namespace std;


Coat::Coat(char size, string colour, double price, int quantity, string photo) :
	size(size),
	color(colour),
	price(price),
	quantity(quantity),
	photo(photo) {}

string Coat::toString()
{
	string res = "";
	res += this->size;
	res += " ";
	res += this->color;
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
	return (this->size == c.size && this->color == c.color);
}

void Coat::testCoat()
{
	Coat a{};
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

ostream& operator<<(ostream& stream, const Coat& c)
{
	stream << c.getSize() << " " << c.getColor() << " " << c.getPrice() << " " << c.getQuantity() << " " << c.getPhoto();
	return stream;
}

istream& operator>>(istream& stream, Coat& c)
{
	char size;
	string colour;
	double price;
	int quantity;
	string photo;
	stream >> size >> colour >> price >> quantity >> photo;
	c.setSize(size);
	c.setColour(colour);
	c.setPrice(price);
	c.setQuantity(quantity);
	c.setPhoto(photo);
	return stream;
}
