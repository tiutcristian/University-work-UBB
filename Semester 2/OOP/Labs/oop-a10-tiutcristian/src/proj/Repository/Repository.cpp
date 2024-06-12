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
		return ((size == '-' || coat.getSize() == size) && coat.getQuantity() > 0);
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

int Repository::getQuantityBySize(char size)
{
	int quantity = 0;
	for (auto coat : this->coats)
		if (coat.getSize() == size)
			quantity += coat.getQuantity();
	return quantity;
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