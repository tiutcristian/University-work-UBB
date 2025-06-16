#include "UI.h"
#include "Services.h"
#include "Domain.h"
#include <iostream>
#include <cassert>
#include <crtdbg.h>

using namespace std;

void runTests()
{
	cout << "Running domain tests..." << endl;
	Coat::testCoat();
	cout << "Domain tests passed!" << endl;
	cout << endl;

	cout << "Running repository tests..." << endl;
	Repository::testRepository();
	cout << "Repository tests passed!" << endl;
	cout << endl;

	cout << "Running basket tests..." << endl;	
	Basket::testBasket();
	cout << "Basket tests passed!" << endl;
	cout << endl;

	cout << "Running services tests..." << endl;
	Services::testService();
	cout << "Services tests passed!" << endl;
}

int main()
{
	{
		//runTests();

		Repository repo("coats.txt");
		Services serv(repo);
		//serv.initializeServ();
		UI ui(serv);
		ui.startUI();
	}

	_CrtDumpMemoryLeaks();

	return 0;
}