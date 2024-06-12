#include "UI.h"
#include "Sensor.h"
#include "TemperatureSensor.h"
#include "HumiditySensor.h"
#include "SmokeSensor.h"

using namespace std;

UI::UI(Device& device) : device(device)
{
	device.addSensor(new TemperatureSensor("producer1", { 1, 2, 3 }, 5));
	device.addSensor(new HumiditySensor("producer2", { 4, 5, 6 }));
	device.addSensor(new SmokeSensor("producer3", { 7, 8, 9 }));
}

void UI::printMenu()
{
	cout << "1. Add a new sensor\n";
	cout << "2. Print all sensors\n";
	cout << "3. Print all alerting sensors\n";
	cout << "4. Save to file all sensors with price less than a value\n";
	cout << "5. Exit\n";
}

void UI::run()
{
int option;
	do
	{
		try
		{
			printMenu();
			cout << "Option: ";
			cin >> option;
			cin.ignore();
			switch (option)
			{
			case 1:
				addSensor();
				break;
			case 2:
				printAllSensors();
				break;
			case 3:
				printAlertingSensors();
				break;
			case 4:
				saveToFile();
				break;
			case 5:
				break;
			default:
				cout << "Invalid option\n";
				break;
			}
		}
		catch (exception& e)
		{
			cout << "Error! " << e.what() << endl;
		}
	} while (option != 5);
}

void UI::addSensor()
{
	string producer;
	cout << "Enter producer: ";
	getline(cin, producer);
	cout << "Enter type: ";
	string type;
	getline(cin, type);
	Sensor* sensor;
	if (type == "temperature")
	{
		double diameter;
		cout << "Enter diameter: ";
		cin >> diameter;
		cout << "Enter recordings number: ";
		int recordingsNumber;
		cin >> recordingsNumber;
		vector<double> recordings;
		for (int i = 0; i < recordingsNumber; i++)
		{
			double value;
			cin >> value;
			recordings.push_back(value);
		}
		sensor = new TemperatureSensor(producer, recordings, diameter);
	}
	else if (type == "humidity")
	{
		cout << "Enter recordings number: ";
		int recordingsNumber;
		cin >> recordingsNumber;
		vector<double> recordings;
		for (int i = 0; i < recordingsNumber; i++)
		{
			double value;
			cin >> value;
			recordings.push_back(value);
		}
		sensor = new HumiditySensor(producer, recordings);
	}
	else if (type == "smoke")
	{
		cout << "Enter recordings number: ";
		int recordingsNumber;
		cin >> recordingsNumber;
		vector<double> recordings;
		for (int i = 0; i < recordingsNumber; i++)
		{
			double value;
			cin >> value;
			recordings.push_back(value);
		}
		sensor = new SmokeSensor(producer, recordings);
	}
	else
	{
		throw exception("Invalid sensor type");
	}
	device.addSensor(sensor);
}

void UI::printAllSensors()
{
	vector<Sensor*> sensors = device.getAllSensors();
	for (Sensor* sensor : sensors)
	{
		cout << sensor->toString() << endl;
	}
}

void UI::printAlertingSensors()
{
	vector<Sensor*> sensors = device.getAlertingSensors();
	for (Sensor* sensor : sensors)
	{
		cout << sensor->toString() << endl;
	}
}

void UI::saveToFile()
{
	string filename;
	cout << "Enter filename: ";
	cin >> filename;
	double value;
	cout << "Enter value: ";
	cin >> value;
	device.writeToFile(filename, value);
}
