#pragma once
#include "Engine.h"

class TurboEngine : public Engine
{
public:
	TurboEngine(double basePrice) : Engine(basePrice) {}
	double getPrice() { return this->basePrice + 100; }
	std::string toString();
};

