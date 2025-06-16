#include "controller.h"
#include <string.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <assert.h>

Service* createService(OffersRepo* r, OperationsStack* undoS, OperationsStack* redoS)
{
	Service* s = (Service*)malloc(sizeof(Service));
	if (s == NULL)
		return NULL;
	s->repo = r;
	s->undoStack = undoS;
	s->redoStack = redoS;
	return s;
}

void destroyService(Service* s)
{
	destroyOffersVector(s->repo);
	destroyStack(s->undoStack);
	destroyStack(s->redoStack);
	free(s);
}

int addOfferServ(Service* s, char* type, char* destination, int day, int month, int year, int price)
{
	Offer* offer = createOffer(type, destination, day, month, year, price);
	int res = addOffer(s->repo, offer);

	if (res == 0)
	{
		Operation* o = createOperation(offer, "add");
		push(s->undoStack, o);
		clearStack(s->redoStack);
	}
	else
		destroyOffer(offer);

	return res;
}

int removeOfferServ(Service* s, char* destination, int day, int month, int year)
{
	Offer* offer = findOffer(s->repo, destination, day, month, year);
	Operation* o = createOperation(offer, "remove");
	int res = deleteOffer(s->repo, offer);

	if (res == 0)
	{
		push(s->undoStack, o);
		clearStack(s->redoStack);
	}
	else
		destroyOperation(o);

	return res;
}

OffersRepo* getRepo(Service* s)
{
	return s->repo;
}

int undo(Service* s)
{
	if (isEmpty(s->undoStack))
		return -1;

	Operation* operation = pop(s->undoStack);
	push(s->redoStack, operation);
	Offer* offer = getOffer(operation);

	if (strcmp(getOperationType(operation), "add") == 0)
		deleteOffer(s->repo, offer);
	else if (strcmp(getOperationType(operation), "remove") == 0)
		addOffer(s->repo, copyOffer(offer));

	return 0;
}

int redo(Service* s)
{
	if (isEmpty(s->redoStack))
		return -1;

	Operation* operation = pop(s->redoStack);
	push(s->undoStack, operation);
	Offer* offer = getOffer(operation);

	if (strcmp(getOperationType(operation), "add") == 0)
		addOffer(s->repo, copyOffer(offer));
	else if (strcmp(getOperationType(operation), "remove") == 0)
		deleteOffer(s->repo, offer);

	return 0;
}


/// <summary>
/// Sorts the offers by price.
/// </summary>
/// <param name="offersVector"></param>
void sortOffersByPrice(OffersRepo* offersVector)
{
	int n = getRepoLength(offersVector);
	for (int i = 0; i < n-1; i++)
		for (int j = i + 1; j < n; j++)
			if (getPrice((Offer*)get(offersVector->offers, i)) > getPrice((Offer*)get(offersVector->offers, j)))
				swapOffers(offersVector, i, j);
}


void filterByDestination(Service* s, char* substr, char* result)
{
	OffersRepo* filterVector = createOffersRepo();
	int n = getRepoLength(s->repo);
	for (int i = 0; i < n; i++)
	{
		Offer* offer = getOfferOnPos(s->repo, i);
		char* destination = getDestination(offer);
		char* result = strstr(destination, substr);
		if (result != NULL || strcmp(substr, "-") == 0)
			addOffer(filterVector, copyOffer(offer));
	}
	sortOffersByPrice(filterVector);
	getOffersAsString(filterVector, result);
	destroyOffersVector(filterVector);
}

/// <summary>
/// Compares two dates.
/// </summary>
/// <param name="day1">- The day of the first date.</param>
/// <param name="month1">- The month of the first date.</param>
/// <param name="year1">- The year of the first date.</param>
/// <param name="day2">- The day of the second date.</param>
/// <param name="month2">- The month of the second date.</param>
/// <param name="year2">- The year of the second date.</param>
/// <returns>-1 if the first date is earlier, 1 if the second date is earlier, 0 if they are equal.</returns>
int compareDates(int day1, int month1, int year1, int day2, int month2, int year2)
{
	if (year1 < year2)
		return -1;
	if (year1 > year2)
		return 1;
	if (month1 < month2)
		return -1;
	if (month1 > month2)
		return 1;
	if (day1 < day2)
		return -1;
	if (day1 > day2)
		return 1;
	return 0;
}

void filterByTypeAndDate(Service* s, char* type, int day, int month, int year, char* result)
{
	OffersRepo* filterVector = createOffersRepo();
	for (int i = 0; i < getRepoLength(s->repo); i++)
	{
		Offer* offer = getOfferOnPos(s->repo, i);
		if (strcmp(getType(offer), type) == 0 &&
			compareDates(day, month, year, getDay(offer), getMonth(offer), getYear(offer)) < 0)
			addOffer(filterVector, copyOffer(offer));
	}
	getOffersAsString(filterVector, result);
	destroyOffersVector(filterVector);
}

void testsController()
{
	// Set up
	OffersRepo* repo = createOffersRepo();
	OperationsStack* undoStack = createStack();
	OperationsStack* redoStack = createStack();
	Service* service = createService(repo, undoStack, redoStack);

	// Test getRepoLength
	assert(getRepoLength(getRepo(service)) == 0);

	// Test add-undo-redo
	assert(addOfferServ(service, "seaside", "dest", 1, 1, 2024, 100) == 0);
	assert(getRepoLength(getRepo(service)) == 1);
	undo(service);
	assert(getRepoLength(getRepo(service)) == 0);
	redo(service);
	assert(getRepoLength(getRepo(service)) == 1);
	char str[200];
	OffersRepo* rp = getRepo(service);
	Offer* offer = rp->offers->elems[0];
	offerToString(offer, str);
	assert(strcmp(str, "Type: seaside, Destination: dest, Departure date: 1/1/2024, Price: 100") == 0);

	// Test remove-undo-redo
	assert(removeOfferServ(service, "dest", 1, 1, 2024) == 0);
	assert(getRepoLength(getRepo(service)) == 0);
	undo(service);
	assert(getRepoLength(getRepo(service)) == 1);
	rp = getRepo(service);
	offer = rp->offers->elems[0];
	offerToString(offer, str);
	assert(strcmp(str, "Type: seaside, Destination: dest, Departure date: 1/1/2024, Price: 100") == 0);
	redo(service);
	assert(getRepoLength(getRepo(service)) == 0);

	// Test destroy
	destroyService(service);
}

void extendedTestsController()
{
	// Set up
	OffersRepo* repo = createOffersRepo();
	OperationsStack* undoStack = createStack();
	OperationsStack* redoStack = createStack();
	Service* service = createService(repo, undoStack, redoStack);
	char result[1000];

	// Test add-undo-redo
	assert(addOfferServ(service, "seaside", "dest", 1, 1, 2024, 100) == 0);
	assert(addOfferServ(service, "mountain", "dest2", 1, 1, 2024, 200) == 0);
	assert(addOfferServ(service, "city break", "dest3", 1, 1, 2024, 300) == 0);
	assert(getRepoLength(getRepo(service)) == 3);
	undo(service);
	assert(getRepoLength(getRepo(service)) == 2);
	offerToString(getOfferOnPos(getRepo(service), 1), result);
	assert(strcmp(result, "Type: mountain, Destination: dest2, Departure date: 1/1/2024, Price: 200") == 0);
	redo(service);
	assert(getRepoLength(getRepo(service)) == 3);
	offerToString(getOfferOnPos(getRepo(service), 2), result);
	assert(strcmp(result, "Type: city break, Destination: dest3, Departure date: 1/1/2024, Price: 300") == 0);

	// Test remove-undo-redo
	assert(removeOfferServ(service, "dest", 1, 1, 2024) == 0);
	assert(removeOfferServ(service, "dest2", 1, 1, 2024) == 0);
	assert(removeOfferServ(service, "dest3", 1, 1, 2024) == 0);
	assert(getRepoLength(getRepo(service)) == 0);
	undo(service);
	assert(getRepoLength(getRepo(service)) == 1);
	offerToString(getOfferOnPos(getRepo(service), 0), result);
	assert(strcmp(result, "Type: city break, Destination: dest3, Departure date: 1/1/2024, Price: 300") == 0);
	undo(service);
	assert(getRepoLength(getRepo(service)) == 2);
	offerToString(getOfferOnPos(getRepo(service), 1), result);
	assert(strcmp(result, "Type: mountain, Destination: dest2, Departure date: 1/1/2024, Price: 200") == 0);
	undo(service);
	assert(getRepoLength(getRepo(service)) == 3);
	offerToString(getOfferOnPos(getRepo(service), 2), result);
	assert(strcmp(result, "Type: seaside, Destination: dest, Departure date: 1/1/2024, Price: 100") == 0);
	redo(service);
	assert(getRepoLength(getRepo(service)) == 2);
	offerToString(getOfferOnPos(getRepo(service), 1), result);
	assert(strcmp(result, "Type: mountain, Destination: dest2, Departure date: 1/1/2024, Price: 200") == 0);
	redo(service);
	assert(getRepoLength(getRepo(service)) == 1);
	offerToString(getOfferOnPos(getRepo(service), 0), result);
	assert(strcmp(result, "Type: city break, Destination: dest3, Departure date: 1/1/2024, Price: 300") == 0);
	redo(service);
	assert(getRepoLength(getRepo(service)) == 0);

	// Test filterByDestination
	assert(addOfferServ(service, "seaside", "dest1", 1, 1, 2024, 100) == 0);
	assert(addOfferServ(service, "mountain", "dest2", 1, 1, 2024, 200) == 0);
	assert(addOfferServ(service, "city break", "dest3", 1, 1, 2024, 300) == 0);
	filterByDestination(service, "dest1", result);
    assert(strcmp(result, "Type: seaside, Destination: dest1, Departure date: 1/1/2024, Price: 100\n") == 0);
    filterByDestination(service, "dest2", result);
    assert(strcmp(result, "Type: mountain, Destination: dest2, Departure date: 1/1/2024, Price: 200\n") == 0);
    filterByDestination(service, "dest3", result);
    assert(strcmp(result, "Type: city break, Destination: dest3, Departure date: 1/1/2024, Price: 300\n") == 0);
    filterByDestination(service, "-", result);
    assert(strcmp(result, "Type: seaside, Destination: dest1, Departure date: 1/1/2024, Price: 100\nType: mountain, Destination: dest2, Departure date: 1/1/2024, Price: 200\nType: city break, Destination: dest3, Departure date: 1/1/2024, Price: 300\n") == 0);
	filterByDestination(service, "dest", result);
	assert(strcmp(result, "Type: seaside, Destination: dest1, Departure date: 1/1/2024, Price: 100\nType: mountain, Destination: dest2, Departure date: 1/1/2024, Price: 200\nType: city break, Destination: dest3, Departure date: 1/1/2024, Price: 300\n") == 0);

    // Test filterByTypeAndDate
    filterByTypeAndDate(service, "seaside", 1, 1, 2023, result);
    assert(strcmp(result, "Type: seaside, Destination: dest1, Departure date: 1/1/2024, Price: 100\n") == 0);
    filterByTypeAndDate(service, "mountain", 1, 1, 2023, result);
    assert(strcmp(result, "Type: mountain, Destination: dest2, Departure date: 1/1/2024, Price: 200\n") == 0);
    filterByTypeAndDate(service, "city break", 1, 1, 2023, result);
    assert(strcmp(result, "Type: city break, Destination: dest3, Departure date: 1/1/2024, Price: 300\n") == 0);
    filterByTypeAndDate(service, "seaside", 1, 1, 2025, result);
    assert(strcmp(result, "") == 0);

	// Test destroy
	destroyService(service);
}
