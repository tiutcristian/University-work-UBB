#pragma once
#include "domain.h"
#include "DynamicArray.h"

typedef struct {
	DynamicArray* offers;
} OffersRepo;

/// <summary>
/// Creates an OffersRepo.
/// </summary>
OffersRepo* createOffersRepo();

/// <summary>
/// Initializes dynamic array with 10 offers.
/// </summary>
void createInitialOffers(OffersRepo* offersVector);

/// <summary>
/// Destroys a given offers repository.
/// </summary>
void destroyOffersVector(OffersRepo* offersVector);

/// <summary>
/// Finds an offer in the repository.
/// </summary>
/// <param name="offersVector">- The dynamic array of offers.</param>
/// <param name="destination">- The destination of the offer.</param>
/// <param name="day">- The day of the departure date.</param>
/// <param name="month">- The month of the departure date.</param>
/// <param name="year">- The year of the departure date.</param>
Offer* findOffer(OffersRepo* offersVector, char* destination, int day, int month, int year);

/// <summary>
/// Adds an offer to the offers array.
/// </summary>
/// <param name="offersVector">- The dynamic array of offers.</param>
/// <param name="offer">- The offer to be added.</param>
/// <returns>0 if offer was added successfully and -1 otherwise.</returns>
int addOffer(OffersRepo* offersVector, Offer* offer);

/// <summary>
/// Deletes an offer from the offers array.
/// </summary>
/// <param name="offersVector">The offers</param>
/// <param name="destination"></param>
/// <param name="day"></param>
/// <param name="month"></param>
/// <param name="year"></param>
/// <returns>1 if found and 0 otherwise</returns>
int deleteOffer(OffersRepo* offersVector, Offer* offer);

/// <summary>
/// Gets the length of the offers repo.
/// </summary>
/// <param name="offersVector">- The repository of offers.</param>
/// <returns>The length of the offers repo.</returns>
int getRepoLength(OffersRepo* offersVector);

/// <summary>
/// Gets the offer on a given position.
/// </summary>
/// <param name="offersVector">- The repository of offers.</param>
/// <param name="pos">- The position.</param>
/// <returns>The offer on the given position.</returns>
Offer* getOfferOnPos(OffersRepo* offersVector, int pos);

/// <summary>
/// Gets offers represented as a string.
/// </summary>
/// <param name="offersVector">- The repository of offers.</param>
/// <param name="offers">- The string of char containing the offers.</param>
void getOffersAsString(OffersRepo* offersVector, char* offers);

/// <summary>
/// Swap 2 offers.
/// </summary>
/// <param name="offersVector">- The repository of offers.</param>
/// <param name="i">- The first position.</param>
/// <param name="j">- The second position.</param>
void swapOffers(OffersRepo* offersVector, int i, int j);

// Tests
void testsRepo();