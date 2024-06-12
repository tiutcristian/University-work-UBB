// Tourism agency \\

/*
Each Offer has a type 
(
	seaside, 
	mountain,
	city break
), 
a destination, 
a departure date,
a price. 


(a) Add, delete and update an offer. (uniquely identified by its destination and departure date)

(b) Display all tourism offers whose destinations contain a given string (if the string is empty, all destinations are considered), 
and show them sorted ascending by price.

(c) Display all offers of a given type, having their departure after a given date.

(d) Provide multiple undo and redo functionality. 
Each step will undo/redo the previous operation performed by the user.
*/

#include "ui.h"
#include <crtdbg.h>
#include <stdio.h>

void runTests()
{
	printf("Running tests...\n");
	testsDynamicArray();
	printf("Dynamic array passed\n");
	testsOffer();
	printf("Offer passed\n");
	testsRepo();
	printf("Repo passed\n");
	testsStack();
	printf("Stack passed\n");
	testsController();
	printf("Controller passed\n");
	extendedTestsController();
	printf("Extended controller passed\n");
}

void runApp()
{
	OffersRepo* offersVector = createOffersRepo();
	createInitialOffers(offersVector);
	OperationsStack* undoStack = createStack();
	OperationsStack* redoStack = createStack();
	Service* service = createService(offersVector, undoStack, redoStack);
	UI* ui = createUI(service);

	startUI(ui);

	destroyUI(ui);
}

int main()
{
	//runTests();
	runApp();

	_CrtDumpMemoryLeaks();
	return 0;
}

