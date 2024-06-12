#include "Refrigerator.h"
#include <sstream>

double Refrigerator::consumedElectricity()
{
	if (electricityUsageClass == "A")
		return 90;
	else
		return 60;
}

std::string Refrigerator::toString()
{
	std::string baseString = Appliance::toString();
	std::stringstream ss;
	ss << baseString << ", type: refrigerator, electricity usage class: " << electricityUsageClass;
	return ss.str();
}
