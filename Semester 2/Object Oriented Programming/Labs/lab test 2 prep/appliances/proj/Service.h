#pragma once
#include "Appliance.h"
#include <vector>

class Service
{
private:
	std::vector<Appliance*> appliances;

public:
	Service() {}
	~Service() { for (auto a : appliances) delete a; }
	void addAppliance(Appliance* a) { appliances.push_back(a); }
	std::vector<Appliance*> getAllAppliances() { return appliances; }
	std::vector<Appliance*> getAppliancesWithConsumedElectricityLessThan(double maxElectricity);
	std::vector<Appliance*> getAllInefficient();
	void writeToFile(std::string fileName, double maxElectricity);
	bool isIDUnique(std::string id);
};

