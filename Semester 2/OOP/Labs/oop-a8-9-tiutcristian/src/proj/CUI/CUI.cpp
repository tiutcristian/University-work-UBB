#include "CUI.h"
#include <iostream>
#include <string>
#include "../Repository/RepositoryExceptions.h"
#include "../Basket/CSVBasket.h"
#include "../Basket/HTMLBasket.h"

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

void UI::shoppingSession(char typeOfBasket)
{
	char size = readChar("Size: ");
	Repository filteredRepo = this->serv.filterBySize(size);
	int crtPos = 0;
	double crtSum = 0;
	unique_ptr<FileBasket> basket;
	if (typeOfBasket == 'c')
		basket = make_unique<CSVBasket>("basket.csv");
	else
		basket = make_unique<HTMLBasket>("basket.html");
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
				basket->addCoat(coat);
				basket->writeToFile();
				filteredRepo[crtPos].setQuantity(filteredRepo[crtPos].getQuantity() - 1);
				this->serv.decrementQuantity(size, coat.getColor());
				crtSum += filteredRepo[crtPos].getPrice();
				cout << "Coat added to basket!" << endl;
			}
		else if (cmd == 'n')
		{
			cout << "1. Proceed to the next coat" << endl;
			cout << "2. Display shopping basket in file" << endl;
			cout << "0. End shopping session" << endl;
			int cmd = readInteger("Enter command: ");
			if (cmd == 0)
			{
				cout << "Shopping session ended!" << endl;
				break;
			}
			else if (cmd == 2)
				basket->displayBasket();
			else
				cout << "Invalid command!" << endl;
		}
		else
			cout << "Invalid command!" << endl;
		crtPos = (crtPos + 1) % filteredRepo.getSize();
		cout << endl;
	}
	cout << "Total sum: " << crtSum << endl;
	cout << "Basket: " << endl << basket->toString() << endl;
}

void UI::runAdminUI()
{
	cout << "    Admin mode\n";
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
			try {
				this->serv.add(size, color, price, quantity, photo);
				cout << "Coat added successfully!" << endl;
			}
			catch (CoatException& e)
			{
				for (auto s : e.getErrors())
					cout << s;
			}
			catch (RepositoryException& e) {
				cout << e.what() << endl;
			}
			catch (FileException& e)
			{
				cout << e.what() << endl;
			}
		}
		else if (cmd == 2)
		{
			char size = readChar("Size: ");
			string color = readString("Color: ");
			try {
				this->serv.remove(size, color);
				cout << "Coat removed successfully!" << endl;
			}
			catch (RepositoryException& ex) {
				cout << ex.what() << endl;
			}
		}
		else if (cmd == 3)
		{
			char size = readChar("Size: ");
			string color = readString("Color: ");
			double price = readDouble("New price: ");
			int quantity = readInteger("New quantity: ");
			string photo = readString("New photo: ");
			try {
				this->serv.update(size, color, price, quantity, photo);
				cout << "Coat updated successfully!" << endl;
			}
			catch (CoatException& e)
			{
				for (auto s : e.getErrors())
					cout << s;
			}
			catch (RepositoryException& ex) 
			{
				cout << ex.what() << endl;
			}
			catch (FileException& e)
			{
				cout << e.what() << endl;
			}
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
	cout << "    User mode\n";
	cout << "CSV or HTML basket?" << endl;
	char typeOfBasket;
	do
	{
		typeOfBasket = readChar("[c/h]: ");
	}
	while (typeOfBasket != 'c' && typeOfBasket != 'h');

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
			this->shoppingSession(typeOfBasket);
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