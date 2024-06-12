#pragma once
#include <string>
#include "Engine.h"

class Car
{
private:
	std::string bodyStyle;
	Engine* engine;
public:
	Car(std::string bodyStyle, std::string engineType, int autonomy);
	~Car();
	double computePrice() { return engine->getPrice(); }
	std::string toString();
};

