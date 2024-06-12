#pragma once
#include "Appliance.h"

class DishWasher : public Appliance
{
private:
	double consumedEnergyForOneHour;

public:
	DishWasher(std::string id, double consumedEnergyForOneHour) : Appliance(id), consumedEnergyForOneHour(consumedEnergyForOneHour) {}
	double consumedElectricity() override { return 20 * consumedEnergyForOneHour; }
	std::string toString() override;
};

