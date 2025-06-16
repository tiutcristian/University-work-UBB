#include "Services.h"
#include <cassert>
#include <iostream>

using namespace std;

void Services::initializeServ()
{
	this->add('S', "Blue", 19.50, 20, "www.example.com/1");
	this->add('M', "Red", 29.50, 10, "www.example.com/2");
	this->add('L', "Green", 59.99, 5, "www.example.com/3");
	this->add('S', "Yellow", 19.50, 20, "www.example.com/4");
	this->add('M', "Black", 29.50, 10, "www.example.com/5");
	this->add('L', "White", 59.99, 5, "www.example.com/6");
	this->add('S', "Purple", 19.50, 20, "www.example.com/7");
	this->add('M', "Orange", 29.50, 10, "www.example.com/8");
	this->add('L', "Pink", 59.99, 5, "www.example.com/9");
	this->add('S', "Brown", 19.50, 20, "www.example.com/10");
}

bool Services::add(char size, string color, double price, int quantity, string photo)
{
	return this->repo.addCoat(size, color, price, quantity, photo);
}

bool Services::remove(char size, string color)
{
    return this->repo.deleteCoat(size, color);
}

bool Services::update(char size, string color, double newPrice, int newQuantity, string newPhoto)
{
	return this->repo.updateCoat(size, color, newPrice, newQuantity, newPhoto);
}

string Services::getElementsAsString()
{
	string elements = this->repo.toString();
	if (elements == "")
		return "No coats in the repository\n";
	return elements;
}

void Services::testService()
{
	Repository repo;
	Services serv{ repo };

    // Test add function
    assert(serv.add('S', "Red", 29.99, 5, "red_coat.jpg") == true);
    assert(serv.add('M', "Blue", 39.99, 3, "blue_coat.jpg") == true);
    assert(serv.add('L', "Green", 49.99, 2, "green_coat.jpg") == true);
    assert(serv.add('S', "Red", 29.99, 5, "red_coat.jpg") == false); // Duplicate entry

    // Test remove function
    assert(serv.remove('S', "Red") == true);
    assert(serv.remove('M', "Blue") == true);
    assert(serv.remove('L', "Green") == true);
    assert(serv.remove('S', "Red") == false); // Entry not found

	// Add back some removed entries
	assert(serv.add('M', "Blue", 39.99, 3, "blue_coat.jpg") == true);
	assert(serv.add('L', "Green", 49.99, 2, "green_coat.jpg") == true);

    // Test update function
    assert(serv.update('S', "Red", 19.99, 10, "new_red_coat.jpg") == false); // Entry not found
    assert(serv.update('M', "Blue", 49.99, 5, "new_blue_coat.jpg") == true);
    assert(serv.update('L', "Green", 59.99, 3, "new_green_coat.jpg") == true);
    assert(serv.update('S', "Red", 19.99, 10, "new_red_coat.jpg") == false); // Entry not found

	// Test get elements as string function
	assert(serv.getElementsAsString() == "M Blue 49.990000 5 new_blue_coat.jpg\nL Green 59.990000 3 new_green_coat.jpg\n");

    assert(serv.remove('M', "Blue") == true);
    assert(serv.remove('L', "Green") == true);

    assert(serv.getElementsAsString() == "No coats in the repository\n");

	// test initializeServ
	serv.initializeServ();
	assert(serv.getElementsAsString() == 
		"S Blue 19.500000 20 www.example.com/1\n"
		"M Red 29.500000 10 www.example.com/2\n"
		"L Green 59.990000 5 www.example.com/3\n"
		"S Yellow 19.500000 20 www.example.com/4\n"
		"M Black 29.500000 10 www.example.com/5\n"
		"L White 59.990000 5 www.example.com/6\n"
		"S Purple 19.500000 20 www.example.com/7\n"
		"M Orange 29.500000 10 www.example.com/8\n"
		"L Pink 59.990000 5 www.example.com/9\n"
		"S Brown 19.500000 20 www.example.com/10\n");

	serv.decrementQuantity('S', "Blue");
	assert(serv.getElementsAsString() == 
		"S Blue 19.500000 19 www.example.com/1\n"
		"M Red 29.500000 10 www.example.com/2\n"
		"L Green 59.990000 5 www.example.com/3\n"
		"S Yellow 19.500000 20 www.example.com/4\n"
		"M Black 29.500000 10 www.example.com/5\n"
		"L White 59.990000 5 www.example.com/6\n"
		"S Purple 19.500000 20 www.example.com/7\n"
		"M Orange 29.500000 10 www.example.com/8\n"
		"L Pink 59.990000 5 www.example.com/9\n"
		"S Brown 19.500000 20 www.example.com/10\n");

	Repository repo2 = serv.filterBySize('S');
	assert(repo2.toString() == 
		"S Blue 19.500000 19 www.example.com/1\n"
		"S Yellow 19.500000 20 www.example.com/4\n"
		"S Purple 19.500000 20 www.example.com/7\n"
		"S Brown 19.500000 20 www.example.com/10\n");
}
