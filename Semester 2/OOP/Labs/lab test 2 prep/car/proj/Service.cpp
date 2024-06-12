#include "Service.h"
#include <fstream>

Service::~Service()
{
	for (auto c : this->cars)
		delete c;
}

void Service::addCar(std::string bodyStyle, std::string engineType, int autonomy)
{
	Car* c = new Car{ bodyStyle, engineType, autonomy };
	this->cars.push_back(c);
}

std::vector<Car*> Service::getCarsWithMaxPrice(double maxPrice)
{
	std::vector<Car*> result;
	for (auto c : this->cars)
		if (c->computePrice() <= maxPrice)
			result.push_back(c);
	return result;
}

void Service::writeToFile(std::string filename)
{
	std::ofstream fout(filename);
	for (auto c : this->cars)
		fout << c->toString() << "\n";
	fout.close();
}
