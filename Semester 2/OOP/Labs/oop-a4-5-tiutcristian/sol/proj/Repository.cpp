#include "Repository.h"
#include "Domain.h"

Repository::Repository(const Repository& repository)
{
	this->coats = repository.coats;
}

bool Repository::addCoat(char size, const std::string& color, double price, int quantity, const std::string& photo)
{
	if (this->findCoat(size, color) != -1)
		return false;
	this->coats.add(Coat{ size, color, price, quantity, photo });
	return true;
}

bool Repository::updateCoat(char size, const std::string& color, double newPrice, int newQuantity, const std::string& newPhoto)
{
	int pos = this->findCoat(size, color);
	if (pos == -1)
		return false;
	this->coats[pos].setPrice(newPrice);
	this->coats[pos].setQuantity(newQuantity);
	this->coats[pos].setPhoto(newPhoto);
	return true;
}

bool Repository::deleteCoat(char size, const std::string& color)
{
	int pos = this->findCoat(size, color);
	if (pos == -1)
		return false;
	this->coats.remove(pos);
	return true;
}

int Repository::findCoat(char size, const std::string& color)
{
	for (int i = 0; i < this->coats.getSize(); i++)
		if (this->coats[i].getSize() == size && this->coats[i].getColor() == color)
			return i;
	return -1;
}

Repository Repository::filterBySize(char size)
{
	Repository filteredRepository;
	for (int i = 0; i < this->coats.getSize(); i++)
		if (size == '-' || this->coats[i].getSize() == size)
			filteredRepository.coats.add(this->coats[i]);
	return filteredRepository;
}

void Repository::decrementQuantity(char size, const std::string& color)
{
	int pos = this->findCoat(size, color);
	int oldQuantity = this->coats[pos].getQuantity();
	this->coats[pos].setQuantity(oldQuantity - 1);
}

std::string Repository::toString()
{
	std::string allElements = "";
	for (int i = 0; i < this->coats.getSize(); i++)
	{
		std::string crt = this->coats[i].toString();
		allElements += crt;
		allElements += "\n";
	}
	return allElements;
}

void Repository::testRepository()
{
	Repository repository;
	assert(repository.addCoat('M', "red", 100, 10, "photo1") == true);
	assert(repository.addCoat('L', "blue", 200, 20, "photo2") == true);
	assert(repository.addCoat('S', "green", 300, 30, "photo3") == true);
	assert(repository.addCoat('M', "yellow", 400, 40, "photo4") == true);
	assert(repository.addCoat('L', "black", 500, 50, "photo5") == true);
	assert(repository.addCoat('M', "red", 600, 60, "photo6") == false);
	assert(repository.addCoat('L', "blue", 700, 70, "photo7") == false);
	assert(repository.addCoat('S', "green", 800, 80, "photo8") == false);
	assert(repository.addCoat('M', "yellow", 900, 90, "photo9") == false);
	assert(repository.addCoat('L', "black", 1000, 100, "photo10") == false);
	assert(repository.updateCoat('M', "red", 1000, 100, "photo10") == true);
	assert(repository.updateCoat('L', "blue", 900, 90, "photo9") == true);
	assert(repository.updateCoat('S', "green", 800, 80, "photo8") == true);
	assert(repository.updateCoat('M', "yellow", 700, 70, "photo7") == true);
	assert(repository.updateCoat('L', "black", 600, 60, "photo6") == true);
	assert(repository.deleteCoat('M', "red") == true);
	assert(repository.deleteCoat('L', "blue") == true);
	assert(repository.toString() == "S green 800.000000 80 photo8\nM yellow 700.000000 70 photo7\nL black 600.000000 60 photo6\n");
	assert(repository.findCoat('M', "red") == -1);
	assert(repository.findCoat('L', "blue") == -1);
	assert(repository.findCoat('S', "green") == 0);
	assert(repository.findCoat('M', "yellow") == 1);
	assert(repository.findCoat('L', "black") == 2);
	Repository repository2(repository);
	for (int i = 0; i < repository2.coats.getSize(); i++)
		assert(repository[i] == repository2[i]);
	Repository repository3 = repository.filterBySize('M');
	assert(repository3.toString() == "M yellow 700.000000 70 photo7\n");
	repository.decrementQuantity('S', "green");
	assert(repository.coats[0].getQuantity() == 79);
	assert(repository.getSize() == 3);
}

int Basket::findCoat(char size, const std::string& color)
{
	for (int i = 0; i < this->coats.getSize(); i++)
		if (this->coats[i].getSize() == size && this->coats[i].getColor() == color)
			return i;
	return -1;
}

void Basket::addCoat(const Coat& coat)
{
	int pos = this->findCoat(coat.getSize(), coat.getColor());
	if (pos != -1)
		this->coats[pos].setQuantity(this->coats[pos].getQuantity() + coat.getQuantity());
	else
		this->coats.add(coat);
}

std::string Basket::toString()
{
	std::string allElements = "";
	for (int i = 0; i < this->coats.getSize(); i++)
	{
		std::string crt = this->coats[i].toString();
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
	assert(basket.coats[0].getQuantity() == 70);
	assert(basket.coats[1].getQuantity() == 20);
	assert(basket.coats[2].getQuantity() == 30);
	assert(basket.coats[3].getQuantity() == 40);
	assert(basket.coats[4].getQuantity() == 50);
	assert(basket.coats[0].getPrice() == 100);
	assert(basket.coats[1].getPrice() == 200);
	assert(basket.coats[2].getPrice() == 300);
	assert(basket.coats[3].getPrice() == 400);
	assert(basket.coats[4].getPrice() == 500);
	assert(basket.coats[0].getPhoto() == "photo1");
	assert(basket.coats[1].getPhoto() == "photo2");
	assert(basket.coats[2].getPhoto() == "photo3");
	assert(basket.coats[3].getPhoto() == "photo4");
	assert(basket.coats[4].getPhoto() == "photo5");
	assert(basket.toString() == 
		"M red 100.000000 70 photo1\n"
		"L blue 200.000000 20 photo2\n"
		"S green 300.000000 30 photo3\n"
		"M yellow 400.000000 40 photo4\n"
		"L black 500.000000 50 photo5\n");
}
