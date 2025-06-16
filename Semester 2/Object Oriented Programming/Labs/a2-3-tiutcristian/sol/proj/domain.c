#include "domain.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


Offer* createOffer(const char* type, const char* destination, int day, int month, int year, int price)
{
    Offer* offer = malloc(sizeof(Offer));
    if (offer == NULL)
		return NULL;

    strcpy(offer->type, type);
    strcpy(offer->destination, destination);
    offer->day = day;
    offer->month = month;
    offer->year = year;
    offer->price = price;
    return offer;
}


void destroyOffer(Offer* offer)
{
    if (offer == NULL)
		return;
	if (offer->type == NULL)
		return;
	free(offer);
}


Offer* copyOffer(Offer* offer)
{
	if (offer == NULL)
		return NULL;
	Offer* copy = createOffer(offer->type, offer->destination, offer->day, offer->month, offer->year, offer->price);
	return copy;
}


char* getType(Offer* offer)
{
    if (offer == NULL)
		return NULL;
	return offer->type;
}


char* getDestination(Offer* offer)
{
	if (offer == NULL)
		return NULL;
	return offer->destination;
}


int getDay(Offer* offer)
{
	if (offer == NULL)
		return -1;
	return offer->day;
}


int getMonth(Offer* offer)
{
	if (offer == NULL)
		return -1;
	return offer->month;
}


int getYear(Offer* offer)
{
	if (offer == NULL)
		return -1;
	return offer->year;
}


int getPrice(Offer* offer)
{
	if (offer == NULL)
		return -1;
	return offer->price;
}


void offerToString(Offer* offer, char str[])
{
	if (offer == NULL)
	{
		strcpy(str, "");
		return;
	}
	sprintf(
		str,
		"Type: %s, Destination: %s, Departure date: %d/%d/%d, Price: %d",
		offer->type,
		offer->destination,
		offer->day,
		offer->month,
		offer->year,
		offer->price
	);
}

// Tests =======================================================================

void testsOffer()
{
	Offer* offer = createOffer("plane", "Paris", 12, 5, 2021, 100);
	assert(strcmp(getType(offer), "plane") == 0);
	assert(strcmp(getDestination(offer), "Paris") == 0);
	assert(getDay(offer) == 12);
	assert(getMonth(offer) == 5);
	assert(getYear(offer) == 2021);
	assert(getPrice(offer) == 100);
	
	Offer* copy = copyOffer(offer);
	assert(strcmp(getType(copy), "plane") == 0);
	assert(strcmp(getDestination(copy), "Paris") == 0);
	assert(getDay(copy) == 12);
	assert(getMonth(copy) == 5);
	assert(getYear(copy) == 2021);
	assert(getPrice(copy) == 100);
	destroyOffer(copy);

	char* str = malloc(100 * sizeof(char));
	offerToString(offer, str);
	assert(strcmp(str, "Type: plane, Destination: Paris, Departure date: 12/5/2021, Price: 100") == 0);
	free(str);

	destroyOffer(offer);
}