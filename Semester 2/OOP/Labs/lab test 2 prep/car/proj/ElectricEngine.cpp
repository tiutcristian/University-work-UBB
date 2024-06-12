#include "ElectricEngine.h"
#include <sstream>

std::string ElectricEngine::toString()
{
	std::stringstream ss;
	ss << "electric engine with price " << this->basePrice << " and autonomy " << this->autonomy;
	return ss.str();
}
