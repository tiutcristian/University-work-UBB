#include "UI.h"
#include "Services.h"
#include "DynamicVector.h"
#include "Domain.h"
#include <iostream>
#include <cassert>
#include <crtdbg.h>

using namespace std;

void testDynamicVector()
{
	// Test with int
	DynamicVector<int> v{ 2 };
	assert(v.getSize() == 0);

	v.add(10);
	assert(v.getSize() == 1);
	assert(v[0] == 10);

	v.add(20);
	assert(v.getSize() == 2);
	assert(v[1] == 20);

	v.add(30);
	assert(v.getSize() == 3);
	assert(v[2] == 30);

	v.remove(1);
	assert(v.getSize() == 2);
	assert(v[0] == 10);
	assert(v[1] == 30);

	// =======================================================

	// Test with Coat
	DynamicVector<Coat> v2{ 2 };
	assert(v2.getSize() == 0);

	Coat c1('M', "Red", 100, 1, "photo1.jpg");
	v2.add(c1);
	assert(v2.getSize() == 1);
	assert(v2[0] == c1);

	Coat c2('L', "Blue", 200, 2, "photo2.jpg");
	v2.add(c2);
	assert(v2.getSize() == 2);
	assert(v2[1] == c2);

	Coat c3('S', "Green", 150, 3, "photo3.jpg");
	v2.add(c3);
	assert(v2.getSize() == 3);
	assert(v2[2] == c3);

	v2.remove(1);
	assert(v2.getSize() == 2);
	assert(v2[0] == c1);
	assert(v2[1] == c3);

	// =======================================================

	v2 = v2;
	assert(v2.getSize() == 2);
	assert(v2[0] == c1);
	assert(v2[1] == c3);
}

void runTests()
{
	cout << "Running domain tests..." << endl;
	Coat::testCoat();
	cout << "Domain tests passed!" << endl;
	cout << endl;

	cout << "Running dynamic vector tests..." << endl;
	testDynamicVector();
	cout << "Dynamic vector tests passed!" << endl;
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
	//runTests();
	
	{
		Repository repo;
		Services serv{ repo };
		serv.initializeServ();
		UI ui{ serv };
		ui.startUI();
	}

	_CrtDumpMemoryLeaks();

	return 0;
}