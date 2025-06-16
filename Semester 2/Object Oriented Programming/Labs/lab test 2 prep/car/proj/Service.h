#pragma once
#include "Car.h"
#include <vector>
class Service
{
private:
	std::vector<Car*> cars;
public:
	Service() = default;
	~Service();
	void addCar(std::string bodyStyle, std::string engineType, int autonomy);
	std::vector<Car*> getCarsWithMaxPrice(double maxPrice);
	void writeToFile(std::string filename);
};

