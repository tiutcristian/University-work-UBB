#include "Services.h"
#include <cassert>
#include <iostream>
#include "../Repository/RepositoryExceptions.h"

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

void Services::add(char size, string color, double price, int quantity, string photo)
{
	Coat coat{ size, color, price, quantity, photo };
	this->validator.validate(coat);
	this->repo.addCoat(coat);

	this->redoActions.clear();
	unique_ptr<Action> action = make_unique<ActionAdd>(this->repo, coat);
	this->undoActions.push_back(std::move(action));
}

void Services::remove(char size, string color)
{
	Coat c = this->repo.findCoat(size, color);
	this->repo.deleteCoat(c);

	this->redoActions.clear();
	unique_ptr<Action> action = make_unique<ActionRemove>(this->repo, c);
	this->undoActions.push_back(std::move(action));
}

void Services::update(char size, string color, double newPrice, int newQuantity, string newPhoto)
{
	Coat oldCoat = this->repo.findCoat(size, color);
	Coat newCoat{ size, color, newPrice, newQuantity, newPhoto };
	this->validator.validate(newCoat);
	this->repo.updateCoat(oldCoat, newCoat);

	this->redoActions.clear();
	unique_ptr<Action> action = make_unique<ActionUpdate>(this->repo, oldCoat, newCoat);
	this->undoActions.push_back(std::move(action));
}

string Services::getElementsAsString()
{
	string elements = this->repo.toString();
	if (elements == "")
		return "No coats in the repository\n";
	return elements;
}

void Services::undo()
{
	if (this->undoActions.empty())
		throw RepositoryException("No more undos!");

	unique_ptr<Action> action = std::move(this->undoActions.back());
	action->executeUndo();
	this->redoActions.push_back(std::move(action));
	this->undoActions.pop_back();
}

void Services::redo()
{
	if (this->redoActions.empty())
		throw RepositoryException("No more redos!");

	unique_ptr<Action> action = std::move(this->redoActions.back());
	action->executeRedo();
	this->undoActions.push_back(std::move(action));
	this->redoActions.pop_back();
}

void Services::testService()
{
	Repository repo;
	Services serv{ repo };

    // Test add function
	try { serv.add('S', "Red", 29.99, 5, "wwwred_coat.jpg"); assert(true); }
	catch (RepositoryException&) { assert(false); }
	try { serv.add('M', "Blue", 39.99, 3, "wwwblue_coat.jpg"); assert(true); }
	catch (RepositoryException&) { assert(false); }
	try { serv.add('L', "Green", 49.99, 2, "wwwgreen_coat.jpg"); assert(true); }
	catch (RepositoryException&) { assert(false); }
	try { serv.add('S', "Red", 29.99, 5, "wwwred_coat.jpg"); assert(false); }
	catch (RepositoryException&) { assert(true); } // Duplicate entry

    // Test remove function
	try { serv.remove('S', "Red"); assert(true); }
	catch (RepositoryException&) { assert(false); }
	try { serv.remove('M', "Blue"); assert(true); }
	catch (RepositoryException&) { assert(false); }
	try { serv.remove('L', "Green"); assert(true); }
	catch (RepositoryException&) { assert(false); }
	try { serv.remove('S', "Red"); assert(false); }
	catch (RepositoryException&) { assert(true); } // Entry not found

	// Add back some removed entries
	try { serv.add('M', "Blue", 39.99, 3, "wwwblue_coat.jpg"); assert(true); }
	catch (RepositoryException&) { assert(false); }
	try { serv.add('L', "Green", 49.99, 2, "wwwgreen_coat.jpg"); assert(true); }
	catch (RepositoryException&) { assert(false); }

    // Test update function
	try { serv.update('S', "Red", 19.99, 10, "wwwnew_red_coat.jpg"); assert(false); }
	catch (RepositoryException&) { assert(true); } // Entry not found
	try { serv.update('M', "Blue", 49.99, 5, "wwwnew_blue_coat.jpg"); assert(true); }
	catch (RepositoryException&) { assert(false); }
	try	{ serv.update('L', "Green", 59.99, 3, "wwwnew_green_coat.jpg"); assert(true); }
	catch (RepositoryException&) { assert(false); }
	try { serv.update('S', "Red", 19.99, 10, "wwwnew_red_coat.jpg"); assert(false); }
	catch (RepositoryException&) { assert(true); } // Entry not found

	// Test get elements as string function
	assert(serv.getElementsAsString() == "M Blue 49.990000 5 wwwnew_blue_coat.jpg\nL Green 59.990000 3 wwwnew_green_coat.jpg\n");

	try { serv.remove('M', "Blue"); assert(true); }
	catch (RepositoryException&) { assert(false); }
	try { serv.remove('L', "Green"); assert(true); }
	catch (RepositoryException&) { assert(false); }

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
