#pragma once
#include <string>

class Engine
{
protected:
	double basePrice;

public:
	Engine(double basePrice) : basePrice(basePrice) {}
	virtual double getPrice() = 0;
	virtual std::string toString() = 0;
};