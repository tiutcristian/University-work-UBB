#pragma once
#include "Engine.h"

class ElectricEngine : public Engine
{
private:
	int autonomy;
public:
	ElectricEngine(int basePrice, int autonomy) : Engine(basePrice), autonomy(autonomy) {}
	double getPrice() { return basePrice + autonomy * 0.01; }
	std::string toString();
};

