#pragma once
#include "../Services/Services.h"

using namespace std;

class UI
{
private:
	Services& serv;


	static int readInteger(const string& message);
	static double readDouble(const string& message);
	static char readChar(const string& message);
	static string readString(const string& message);
	void printMenu();
	void runAdminUI();
	void runUserUI();
	void printAdminMenu();
	void printUserMenu();
	void shoppingSession(char typeOfBasket);

public:
	UI(Services& serv) : serv{ serv } {}

	void startUI();
};