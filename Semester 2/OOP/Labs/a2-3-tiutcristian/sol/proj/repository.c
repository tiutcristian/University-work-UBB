#pragma once
#include "repository.h"
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


OffersRepo* createOffersRepo()
{
	OffersRepo* offersVector = malloc(sizeof(OffersRepo));
	if (offersVector ==	NULL)
		return NULL;
	offersVector->offers = createDynamicArray(CAPACITY, &destroyOffer);
	return offersVector;
}


void createInitialOffers(OffersRepo* offersVector)
{
	addOffer(offersVector, createOffer("seaside", "Mamaia", 1, 1, 2024, 100));
	addOffer(offersVector, createOffer("mountain", "Zell am See", 2, 3, 2024, 200));
	addOffer(offersVector, createOffer("city break", "Paris", 4, 5, 2025, 300));
	addOffer(offersVector, createOffer("seaside", "Constanta", 6, 7, 2024, 100));
	addOffer(offersVector, createOffer("mountain", "Kaprun", 8, 9, 2024, 200));
	addOffer(offersVector, createOffer("city break", "Rome", 1, 1, 2025, 300));
	addOffer(offersVector, createOffer("seaside", "Mamaia", 1, 2, 2024, 100));
	addOffer(offersVector, createOffer("mountain", "Zell am See", 3, 4, 2024, 200));
	addOffer(offersVector, createOffer("city break", "Paris", 5, 6, 2025, 300));
	addOffer(offersVector, createOffer("seaside", "Mamaia", 7, 8, 2024, 100));
}


void destroyOffersVector(OffersRepo* offersVector)
{
	if (offersVector == NULL)
		return;
	destroy(offersVector->offers);
	free(offersVector);
}


Offer* findOffer(OffersRepo* offersVector, char* destination, int day, int month, int year)
{
	for (int i = 0; i < getLength(offersVector->offers); i++)
	{
		Offer* offer = (Offer*)get(offersVector->offers, i);
		if (strcmp(getDestination(offer), destination) == 0 &&
			getDay(offer) == day &&
			getMonth(offer) == month &&
			getYear(offer) == year)
			return offer;
	}
	return NULL;
}

int getPosition(OffersRepo* offersVector, char* destination, int day, int month, int year)
{
	for (int i = 0; i < getLength(offersVector->offers); i++)
	{
		Offer* offer = (Offer*)get(offersVector->offers, i);
		if (strcmp(getDestination(offer), destination) == 0 &&
			getDay(offer) == day &&
			getMonth(offer) == month &&
			getYear(offer) == year)
			return i;
	}
	return -1;
}


int addOffer(OffersRepo* offersVector, Offer* offer)
{
	if (findOffer(offersVector, getDestination(offer), getDay(offer), getMonth(offer), getYear(offer)) != NULL)
		return -1;
	addElement(offersVector->offers, offer);
	return 0;
}


int deleteOffer(OffersRepo* offersVector, Offer* offer)
{
	if (offersVector == NULL)
		return -1;
	int position = getPosition(
		offersVector, 
		getDestination(offer), 
		getDay(offer), 
		getMonth(offer), 
		getYear(offer)
	);
	if (position == -1)
		return -1;
	deleteElement(offersVector->offers, position);
	return 0;
}

int getRepoLength(OffersRepo* offersVector)
{
	if (offersVector == NULL)
		return -1;
	return getLength(offersVector->offers);
}

Offer* getOfferOnPos(OffersRepo* offersVector, int pos)
{
	if (offersVector == NULL)
		return NULL;
	Offer* offer = (Offer*)get(offersVector->offers, pos);
	return offer;
}


void getOffersAsString(OffersRepo* offersVector, char offers[])
{
	if (offers == NULL)
		return NULL;
	offers[0] = '\0';
	for (int i = 0; i < getRepoLength(offersVector); i++)
	{
		char tmp[200];
		offerToString((Offer*)get(offersVector->offers, i), tmp);
		strcat(offers, tmp);
		strcat(offers, "\n");
	}
}

void swapOffers(OffersRepo* offersVector, int i, int j)
{
	Offer* aux = (Offer*)get(offersVector->offers, i);
	set(offersVector->offers, i, (Offer*)get(offersVector->offers, j));
	set(offersVector->offers, j, aux);
}

void testsRepo()
{
	OffersRepo* offersVector = createOffersRepo();
	assert(getRepoLength(offersVector) == 0);
	Offer* offer1 = createOffer("seaside", "Mamaia", 1, 1, 2024, 100);
	Offer* offer2 = createOffer("mountain", "Zell am See", 2, 3, 2024, 200);
	Offer* offer3 = createOffer("city break", "Paris", 4, 5, 2025, 300);
	addOffer(offersVector, offer1);
	addOffer(offersVector, offer2);
	addOffer(offersVector, offer3);
	assert(getRepoLength(offersVector) == 3);
	assert(findOffer(offersVector, "Mamaia", 1, 1, 2024) == offer1);
	assert(findOffer(offersVector, "Zell am See", 2, 3, 2024) == offer2);
	assert(findOffer(offersVector, "Paris", 4, 5, 2025) == offer3);
	assert(findOffer(offersVector, "Mamaia", 2, 3, 2024) == NULL);
	assert(getOfferOnPos(offersVector, 0) == offer1);
	assert(getOfferOnPos(offersVector, 1) == offer2);
	assert(getOfferOnPos(offersVector, 2) == offer3);
	swapOffers(offersVector, 0, 1);
	assert(getOfferOnPos(offersVector, 0) == offer2);
	assert(getOfferOnPos(offersVector, 1) == offer1);
	deleteOffer(offersVector, offer1);
	assert(getRepoLength(offersVector) == 2);
	deleteOffer(offersVector, offer2);
	assert(getRepoLength(offersVector) == 1);
	deleteOffer(offersVector, offer3);
	assert(getRepoLength(offersVector) == 0);
	destroyOffersVector(offersVector);
}

