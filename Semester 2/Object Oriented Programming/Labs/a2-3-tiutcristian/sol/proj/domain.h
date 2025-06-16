#pragma once
typedef struct {
	char type[11];
	char destination[100];
	int day;
	int month;
	int year;
	int price;
} Offer;

/// <summary>
/// Creates an offer.
/// </summary>
/// <param name="type">- The type of the offer.</param>
/// <param name="destination">- The destination of the offer.</param>
/// <param name="day">- The day of the departure date.</param>	
/// <param name="month">- The month of the departure date.</param>
/// <param name="year">- The year of the departure date.</param>
/// <param name="price">- The price of the offer.</param>
/// <returns>A pointer to the newly created offer.</returns>
Offer* createOffer(const char* type, const char* destination, int day, int month, int year, int price);

/// <summary>
/// Destroys an offer.
/// </summary>
/// <param name="offer">- The offer to be destroyed.</param>
void destroyOffer(Offer* offer);

/// <summary>
/// Creates a copy of an offer.
/// </summary>
/// <param name="offer">- The offer to be copied.</param>
/// <returns>A pointer to the newly created offer.</returns>
Offer* copyOffer(Offer* offer);

/// <summary>
/// Gets the type of an offer.
/// </summary>
/// <param name="offer">- The offer.</param>
/// <returns>A pointer to the type of the offer.</returns>
char* getType(Offer* offer);

/// <summary>
/// Gets the destination of an offer.
/// </summary>
/// <param name="offer">- The offer.</param>
/// <returns>A pointer to the destination of the offer.</returns>
char* getDestination(Offer* offer);

/// <summary>
/// Gets the day of the departure date of an offer.
/// </summary>
/// <param name="offer">- The offer.</param>
/// <returns>The day of the departure date of the offer.</returns>
int getDay(Offer* offer);

/// <summary>
/// Gets the month of the departure date of an offer.
/// </summary>
/// <param name="offer">- The offer.</param>
/// <returns>The month of the departure date of the offer.</returns>
int getMonth(Offer* offer);

/// <summary>
/// Gets the year of the departure date of an offer.
/// </summary>
/// <param name="offer">- The offer.</param>
/// <returns>The year of the departure date of the offer.</returns>
int getYear(Offer* offer);

/// <summary>
/// Gets the price of an offer.
/// </summary>
/// <param name="offer">- The offer.</param>
/// <returns>The price of the offer.</returns>
int getPrice(Offer* offer);

/// <summary>
/// Converts an offer to a string.
/// </summary>
/// <param name="offer">- The offer.</param>
/// <param name="str">- The string to be modified.</param>
void offerToString(Offer* offer, char str[]);