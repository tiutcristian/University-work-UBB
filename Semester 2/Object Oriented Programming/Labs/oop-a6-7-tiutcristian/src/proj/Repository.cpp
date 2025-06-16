#include "Repository.h"
#include <cassert>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
#include "RepositoryExceptions.h"

Repository::Repository(const std::string& filename) : filename(filename)
{
	if (filename != "tmp.txt")
		this->loadFromFile();
}

void Repository::saveToFile()
{
	std::ofstream file(filename);
	for (auto coat : this->coats)
		file << coat << "\n";
	file.close();
}

void Repository::loadFromFile()
{
std::ifstream file(filename);
	this->coats.clear();
	Coat coat;
	while (file>>coat)
		this->coats.push_back(coat);
	file.close();
}

void Repository::addCoat(const Coat& c)
{
	try
	{
		auto it = findCoatIt(c.getSize(), c.getColor());
		throw RepositoryDuplicateException();
	}
	catch (RepositoryNotFoundException&) {}
	this->coats.push_back(c);
	this->saveToFile();
}

void Repository::updateCoat(const Coat& oldCoat, const Coat& newCoat)
{
	auto it = findCoatIt(oldCoat.getSize(), oldCoat.getColor());
	if (it == this->coats.end())
		throw RepositoryNotFoundException();
	this->coats.erase(it);
	this->coats.push_back(newCoat);
	saveToFile();
}

void Repository::deleteCoat(const Coat& c)
{
	auto it = findCoatIt(c.getSize(), c.getColor());
	if (it == this->coats.end())
		throw RepositoryNotFoundException();
	this->coats.erase(it);
	saveToFile();
}

std::vector<Coat>::iterator Repository::findCoatIt(char size, const std::string& color)
{
	auto it = find_if(
		this->coats.begin(),
		this->coats.end(),
		[size, color](const Coat& coat) {
			return coat.getSize() == size && coat.getColor() == color;
		}
	);
	if (it == this->coats.end())
		throw RepositoryNotFoundException();
	return it;
}

Repository Repository::filterBySize(char size)
{
	Repository filteredRepository;
	auto filterCondition = [size](const Coat& coat) {
		return (size == '-' || coat.getSize() == size);
	};
	std::copy_if(this->coats.begin(), this->coats.end(), std::back_inserter(filteredRepository.coats), filterCondition);
	return filteredRepository;
}

void Repository::decrementQuantity(char size, const std::string& color)
{
	auto it = findCoatIt(size, color);
	it->setQuantity(it->getQuantity() - 1);
	saveToFile();
}

std::string Repository::toString()
{
	std::string allElements = "";
	for (auto coat : this->coats)
	{
		std::string crt = coat.toString();
		allElements += crt;
		allElements += "\n";
	}
	return allElements;
}

void Repository::testRepository()
{
	Repository repository;

	try { repository.addCoat(Coat{ 'M', "red", 100, 10, "photo1" }); assert(true); }
	catch (RepositoryDuplicateException&) { assert(false); }
	try { repository.addCoat(Coat{ 'L', "blue", 200, 20, "photo2" }); assert(true); }
	catch (RepositoryDuplicateException&) { assert(false); }
	try { repository.addCoat(Coat{ 'S', "green", 300, 30, "photo3" }); assert(true); }
	catch (RepositoryDuplicateException&) { assert(false); }
	try { repository.addCoat(Coat{ 'M', "yellow", 400, 40, "photo4" }); assert(true); }
	catch (RepositoryDuplicateException&) { assert(false); }
	try { repository.addCoat(Coat{ 'L', "black", 500, 50, "photo5" }); assert(true); }
	catch (RepositoryDuplicateException&) { assert(false); }

	try { repository.addCoat(Coat{ 'M', "red", 600, 60, "photo6" }); assert(false); }
	catch (RepositoryDuplicateException&) { assert(true); }
	try { repository.addCoat(Coat{ 'L', "blue", 700, 70, "photo7" }); assert(false); }
	catch (RepositoryDuplicateException&) { assert(true); }
	try { repository.addCoat(Coat{ 'S', "green", 800, 80, "photo8" }); assert(false); }
	catch (RepositoryDuplicateException&) { assert(true); }
	try { repository.addCoat(Coat{ 'M', "yellow", 900, 90, "photo9" }); assert(false); }
	catch (RepositoryDuplicateException&) { assert(true); }
	try { repository.addCoat(Coat{ 'L', "black", 1000, 100, "photo10" }); assert(false); }
	catch (RepositoryDuplicateException&) { assert(true); }

	try { repository.updateCoat(Coat{ 'M', "red", 100, 10, "photo1" }, Coat{ 'M', "red", 1000, 100, "photo10" }); assert(true); }
	catch (RepositoryNotFoundException&) { assert(false); }
	try { repository.updateCoat(Coat{ 'L', "blue", 200, 20, "photo2" }, Coat{ 'L', "blue", 900, 90, "photo9" }); assert(true); }
	catch (RepositoryNotFoundException&) { assert(false); }
	try { repository.updateCoat(Coat{ 'S', "green", 300, 30, "photo3" }, Coat{ 'S', "green", 800, 80, "photo8" }); assert(true); }
	catch (RepositoryNotFoundException&) { assert(false); }
	try { repository.updateCoat(Coat{ 'M', "yellow", 400, 40, "photo4" }, Coat{ 'M', "yellow", 700, 70, "photo7" }); assert(true); }
	catch (RepositoryNotFoundException&) { assert(false); }
	try { repository.updateCoat(Coat{ 'L', "black", 500, 50, "photo5" }, Coat{ 'L', "black", 600, 60, "photo6" }); assert(true); }
	catch (RepositoryNotFoundException&) { assert(false); }
	
	try { repository.deleteCoat(Coat{ 'S', "green", 800, 80, "photo8" }); assert(true); }
	catch (RepositoryNotFoundException&) { assert(false); }
	try { repository.deleteCoat(Coat{ 'M', "yellow", 700, 70, "photo7" }); assert(true); }
	catch (RepositoryNotFoundException&) { assert(false); }

	assert(repository.toString() == 
		"M red 1000.000000 100 photo10\n"
		"L blue 900.000000 90 photo9\n"
		"L black 600.000000 60 photo6\n");

	try { repository.findCoatIt('M', "red"); assert(true); }
	catch (RepositoryNotFoundException&) { assert(false); }
	try { repository.findCoatIt('L', "blue"); assert(true); }
	catch (RepositoryNotFoundException&) { assert(false); }
	try { repository.findCoatIt('S', "green"); assert(false); }
	catch (RepositoryNotFoundException&) { assert(true); }
	try { repository.findCoatIt('M', "yellow"); assert(false); }
	catch (RepositoryNotFoundException&) { assert(true); }
	try { repository.findCoatIt('L', "black"); assert(true); }
	catch (RepositoryNotFoundException&) { assert(false); }

	Repository repository2(repository);
	for (int i = 0; i < repository2.coats.size(); i++)
		assert(repository[i] == repository2[i]);

	Repository repository3 = repository.filterBySize('M');
	assert(repository3.toString() == "M red 1000.000000 100 photo10\n");

	repository.decrementQuantity('L', "blue");
	assert(repository.coats[1].getQuantity() == 89);

	assert(repository.getSize() == 3);
}

Repository::~Repository()
{
	if (this->filename == "tmp.txt")
		std::remove("tmp.txt");
	else
		this->saveToFile();
}

int Basket::findCoat(char size, const std::string& color)
{
	auto it = std::find_if(this->shoppingBasket.begin(), this->shoppingBasket.end(), [size, color](const Coat& coat) { return coat.getSize() == size && coat.getColor() == color; });
	if (it != this->shoppingBasket.end())
		return std::distance(this->shoppingBasket.begin(), it);
	return -1;
}

void Basket::addCoat(const Coat& coat)
{
	int pos = this->findCoat(coat.getSize(), coat.getColor());
	if (pos != -1)
		this->shoppingBasket[pos].setQuantity(this->shoppingBasket[pos].getQuantity() + coat.getQuantity());
	else
		this->shoppingBasket.push_back(coat);
}

std::string Basket::toString()
{
	std::string allElements = "";
	for (auto coat : this->shoppingBasket)
	{
		std::string crt = coat.toString();
		allElements += crt;
		allElements += "\n";
	}
	return allElements;
}

void Basket::testBasket()
{
	Basket basket;
	assert(basket.findCoat('M', "red") == -1);
	basket.addCoat(Coat{ 'M', "red", 100, 10, "photo1" });
	assert(basket.findCoat('M', "red") == 0);
	basket.addCoat(Coat{ 'L', "blue", 200, 20, "photo2" });
	assert(basket.findCoat('L', "blue") == 1);
	basket.addCoat(Coat{ 'S', "green", 300, 30, "photo3" });
	assert(basket.findCoat('S', "green") == 2);
	basket.addCoat(Coat{ 'M', "yellow", 400, 40, "photo4" });
	assert(basket.findCoat('M', "yellow") == 3);
	basket.addCoat(Coat{ 'L', "black", 500, 50, "photo5" });
	assert(basket.findCoat('L', "black") == 4);
	basket.addCoat(Coat{ 'M', "red", 600, 60, "photo6" });
	assert(basket.shoppingBasket[0].getQuantity() == 70);
	assert(basket.shoppingBasket[1].getQuantity() == 20);
	assert(basket.shoppingBasket[2].getQuantity() == 30);
	assert(basket.shoppingBasket[3].getQuantity() == 40);
	assert(basket.shoppingBasket[4].getQuantity() == 50);
	assert(basket.shoppingBasket[0].getPrice() == 100);
	assert(basket.shoppingBasket[1].getPrice() == 200);
	assert(basket.shoppingBasket[2].getPrice() == 300);
	assert(basket.shoppingBasket[3].getPrice() == 400);
	assert(basket.shoppingBasket[4].getPrice() == 500);
	assert(basket.shoppingBasket[0].getPhoto() == "photo1");
	assert(basket.shoppingBasket[1].getPhoto() == "photo2");
	assert(basket.shoppingBasket[2].getPhoto() == "photo3");
	assert(basket.shoppingBasket[3].getPhoto() == "photo4");
	assert(basket.shoppingBasket[4].getPhoto() == "photo5");
	assert(basket.toString() == 
		"M red 100.000000 70 photo1\n"
		"L blue 200.000000 20 photo2\n"
		"S green 300.000000 30 photo3\n"
		"M yellow 400.000000 40 photo4\n"
		"L black 500.000000 50 photo5\n");
}
