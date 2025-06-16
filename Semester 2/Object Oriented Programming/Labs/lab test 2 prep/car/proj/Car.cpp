#include "Car.h"
#include "ElectricEngine.h"
#include "TurboEngine.h"
#include <sstream>

Car::Car(std::string bodyStyle, std::string engineType, int autonomy)
{
	this->bodyStyle = bodyStyle;
	if (engineType == "electric")
		this->engine = new ElectricEngine(3000, autonomy);
	else
		this->engine = new TurboEngine(3000);
}

Car::~Car()
{
	delete engine;
}

std::string Car::toString()
{
	std::stringstream ss;
	ss << "Car: " << bodyStyle << " with " << engine->toString();
	return ss.str();
}
