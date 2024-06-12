#pragma once
#include "Appliance.h"

class Refrigerator : public Appliance
{
private:
	std::string electricityUsageClass;
	bool hasFreezer;

public:
	Refrigerator(std::string id, std::string electricityUsageClass, bool hasFreezer) : Appliance(id), electricityUsageClass(electricityUsageClass), hasFreezer(hasFreezer) {}
	double consumedElectricity() override;
	std::string toString() override;
};

