#include "TurboEngine.h"
#include <sstream>

std::string TurboEngine::toString()
{
	std::stringstream ss;
	ss << "turbo engine with price " << this->basePrice;
	return ss.str();
}
