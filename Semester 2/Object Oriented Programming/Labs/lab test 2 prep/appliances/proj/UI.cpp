#include "UI.h"
#include "Refrigerator.h"
#include "DishWasher.h"

using namespace std;

UI::UI(Service& service) : service(service)
{
	service.addAppliance(new Refrigerator("1", "A", true));
	service.addAppliance(new Refrigerator("2", "A++", false));
	service.addAppliance(new DishWasher("3", 1.5));
}

void UI::printMenu()
{
	cout << "Menu:" << endl;
	cout << "1. Add a new appliance." << endl;
	cout << "2. Show all appliances." << endl;
	cout << "3. Show all inefficient appliances." << endl;
	cout << "4. Save to file all appliances under a given energy consumption." << endl;
	cout << "0. Exit." << endl;
}

void UI::runUI()
{
	int option;
	do
	{
		try
		{
			printMenu();
			cout << "Enter option: ";
			cin >> option;
			cin.ignore();
			switch (option)
			{
			case 1:
				addAppliance();
				break;
			case 2:
				showAll();
				break;
			case 3:
				showInefficient();
				break;
			case 4:
				saveToFile();
				break;
			case 0:
				break;
			default:
				cout << "Invalid option." << endl;
				break;
			}
		}
		catch (const std::exception& e)
		{
			cout << "Error! " << e.what() << endl;
		}
	} while (option != 0);
}

void UI::addAppliance()
{
	string id;
	cout << "Enter id: ";
	cin >> id;
	cin.ignore();
	if (!service.isIDUnique(id))
		throw exception("Id already exists.");
	string type;
	cout << "Enter type of appliance: ";
	cin >> type;
	Appliance* appliance;
	if (type == "refrigerator")
	{
		cout << "Enter electricity usage class: ";
		string electricityUsageClass;
		cin >> electricityUsageClass;
		if (electricityUsageClass != "A" && electricityUsageClass != "A++")
			throw exception("Invalid electricity usage class.");
		cout << "Does it inluse a freezer? [y/n]";
		char freezer;
		cin >> freezer;
		if (freezer != 'y' && freezer != 'n')
			throw exception("Invalid input.");
		bool hasFreezer = (freezer == 'y');
		appliance = new Refrigerator(id, electricityUsageClass, hasFreezer);
	}
	else if (type == "dishwasher")
	{
		cout << "Enter consumed electricity per hour: ";
		double consumedElectricityPerHour;
		cin >> consumedElectricityPerHour;
		if (consumedElectricityPerHour < 0)
			throw exception("Invalid consumed electricity per hour.");
		appliance = new DishWasher(id, consumedElectricityPerHour);
	}
	else
		throw exception("Invalid type of appliance.");
	cin.ignore();
	service.addAppliance(appliance);
}

void UI::showAll()
{
	for (Appliance* appliance : service.getAllAppliances())
		cout << appliance->toString() << endl;
}

void UI::showInefficient()
{
	for (Appliance* appliance : service.getAllInefficient())
		cout << appliance->toString() << endl;
}

void UI::saveToFile()
{
	double maxConsumedElectricity;
	cout << "Enter maximum consumed electricity: ";
	cin >> maxConsumedElectricity;
	if (maxConsumedElectricity < 0)
		throw exception("Invalid maximum consumed electricity.");
	cout << "Enter file name: ";
	string fileName;
	cin >> fileName;
	cin.ignore();
	service.writeToFile(fileName, maxConsumedElectricity);
}
