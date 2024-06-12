#include "Appliance.h"
#include <sstream>

std::string Appliance::toString()
{
	std::stringstream ss;
	ss << "id: " << id;
	return ss.str();
}
