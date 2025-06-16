#include "UI.h"
#include <iostream>
#include <string>
using namespace std;

int UI::readInteger(const string& message)
{
	cout << message;
	string number;
	cin >> number;
	while (cin.fail() || number.find_first_not_of("0123456789") != string::npos)
	{
		cin.clear();
		cin.ignore();
		cout << "Invalid number!" << endl;
		cout << message;
		cin >> number;
	}
	int numberInt = stoi(number);
	return numberInt;
}

double UI::readDouble(const string& message)
{
	cout << message;
	string number;
	cin >> number;
	while (cin.fail() || number.find_first_not_of("0123456789.") != string::npos)
	{
		cin.clear();
		cin.ignore();
		cout << "Invalid number!" << endl;
		cout << message;
		cin >> number;
	}
	double numberDouble = stod(number);
	return numberDouble;
}

char UI::readChar(const string& message)
{
	cout << message;
	string character;
	cin >> character;
	while (cin.fail() || character.size() != 1)
	{
		cin.clear();
		cin.ignore();
		cout << "Invalid character!" << endl;
		cout << message;
		cin >> character;
	}
	char characterChar = character[0];
	return characterChar;
}

string UI::readString(const string& message)
{
	cout << message;
	string text;
	cin >> text;
	return text;
}

void UI::printMenu()
{
	cout << "1. Admin mode" << endl;
	cout << "2. User mode" << endl;
	cout << "0. Exit" << endl;
}

void UI::printAdminMenu()
{
	cout << "    1. Add a coat" << endl;
	cout << "    2. Delete a coat" << endl;
	cout << "    3. Update a coat" << endl;
	cout << "    4. Show all coats" << endl;
	cout << "    0. Disconnect from admin mode" << endl;
}

void UI::printUserMenu()
{
	cout << "    0. Disconnect from user mode" << endl;
	cout << "    1. Start shopping session" << endl;
}

void UI::shoppingSession()
{
	char size = readChar("Size: ");
	Repository filteredRepo = this->serv.filterBySize(size);
	int crtPos = 0;
	double crtSum = 0;
	//Repository basket;
	Basket basket;
	while (true)
	{
		cout << "Current coat: " << filteredRepo[crtPos].toString() << endl;
		cout << "Add the coat to the shopping basket?" << endl;
		char cmd = readChar("[y/n]: ");
		if (cmd == 'y')
			if (filteredRepo[crtPos].getQuantity() == 0)
				cout << "Coat out of stock!" << endl;
			else
			{
				Coat coat = filteredRepo[crtPos];
				coat.setQuantity(1);
				basket.addCoat(coat);
				filteredRepo[crtPos].setQuantity(filteredRepo[crtPos].getQuantity() - 1);
				this->serv.decrementQuantity(size, coat.getColor());
				crtSum += filteredRepo[crtPos].getPrice();
				cout << "Coat added to basket!" << endl;
			}
		else if (cmd == 'n')
		{
			cout << "1. Proceed to the next coat" << endl;
			cout << "0. End shopping session" << endl;
			int cmd = readInteger("Enter command: ");
			if (cmd == 0)
			{
				cout << "Shopping session ended!" << endl;
				break;
			}
		}
		else
			cout << "Invalid command!" << endl;
		crtPos = (crtPos + 1) % filteredRepo.getSize();
		cout << endl;
	}
	cout << "Total sum: " << crtSum << endl;
	cout << "Basket: " << endl << basket.toString() << endl;
}

void UI::runAdminUI()
{
	printf("    Admin mode\n");
	while (true)
	{
		printAdminMenu();
		int cmd = readInteger("Enter command: ");
		if (cmd == 1)
		{
			char size = readChar("Size: ");
			string color = readString("Color: ");
			double price = readDouble("Price: ");
			int quantity = readInteger("Quantity: ");
			string photo = readString("Photo: ");
			if (this->serv.add(size, color, price, quantity, photo))
				cout << "Coat added successfully!" << endl;
			else
				cout << "Coat already exists!" << endl;
		}
		else if (cmd == 2)
		{
			char size = readChar("Size: ");
			string color = readString("Color: ");
			if (this->serv.remove(size, color))
				cout << "Coat removed successfully!" << endl;
			else
				cout << "Coat does not exist!" << endl;
		}
		else if (cmd == 3)
		{
			char size = readChar("Size: ");
			string color = readString("Color: ");
			double price = readDouble("New price: ");
			int quantity = readInteger("New quantity: ");
			string photo = readString("New photo: ");
			if (this->serv.update(size, color, price, quantity, photo))
				cout << "Coat updated successfully!" << endl;
			else
				cout << "Coat does not exist!" << endl;
		}
		else if (cmd == 4)
		{
			string coats = this->serv.getElementsAsString();
			cout << coats;
		}
		else if (cmd == 0)
		{
			cout << "Disconnected from admin mode!" << endl;
			break;
		}
		else
			cout << "Invalid command!" << endl;
	}
}

void UI::runUserUI()
{
	printf("    User mode\n");
	while (true)
	{
		printUserMenu();
		int cmd = readInteger("Enter command: ");
		if (cmd == 0)
		{
			cout << "Disconnected from user mode!" << endl;
			break;
		}
		else if (cmd == 1)
			this->shoppingSession();
		else
			cout << "Invalid command!" << endl;
	}
}

void UI::startUI()
{
	while (true)
	{
		printMenu();
		int cmd = readInteger("Enter command: ");
		if (cmd == 0)
			break;
		else if (cmd == 1)
			runAdminUI();
		else if (cmd == 2)
			runUserUI();
        else
            cout << "Invalid command!" << endl;
	}
}