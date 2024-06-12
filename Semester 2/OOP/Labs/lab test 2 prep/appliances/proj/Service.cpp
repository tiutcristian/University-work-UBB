#include "Service.h"
#include <fstream>

std::vector<Appliance*> Service::getAppliancesWithConsumedElectricityLessThan(double maxElectricity)
{
	std::vector<Appliance*> result;
	for (auto& appliance : appliances)
	{
		if (appliance->consumedElectricity() < maxElectricity)
		{
			result.push_back(appliance);
		}
	}
	return result;
}

std::vector<Appliance*> Service::getAllInefficient()
{
	std::vector<Appliance*> result;
	for (auto& appliance : appliances)
	{
		if (appliance->consumedElectricity() > 100)
		{
			result.push_back(appliance);
		}
	}
	return result;
}

void Service::writeToFile(std::string fileName, double maxElectricity)
{
	std::ofstream file(fileName);
	std::vector<Appliance*> filteredAppliances = getAppliancesWithConsumedElectricityLessThan(maxElectricity);
	for (auto& appliance : filteredAppliances)
	{
		file << appliance->toString() << "\n";
	}
	file.close();
}

bool Service::isIDUnique(std::string id)
{
	for (auto& appliance : appliances)
	{
		if (appliance->getId() == id)
		{
			return false;
		}
	}
	return true;
}
