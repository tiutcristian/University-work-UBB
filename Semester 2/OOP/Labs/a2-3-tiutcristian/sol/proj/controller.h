#pragma once
#include "repository.h"
#include "OperationsStack.h"


typedef struct
{
	OffersRepo* repo;
	OperationsStack* undoStack;
	OperationsStack* redoStack;
} Service;


/// <summary>
/// Creates a Service.
/// </summary>
/// <param name="r">Pointer to the repository.</param>
/// <param name="undoS">Pointer to the undo stack.</param>
/// <param name="redoS">Pointer to the redo stack.</param>
/// <returns>Pointer to the Service.</returns>
Service* createService(OffersRepo* r, OperationsStack* undoS, OperationsStack* redoS);


/// <summary>
/// Destroys a given service.
/// </summary>
/// <param name="s">Pointer to the Service.</param>
void destroyService(Service* s);


/// <summary>
/// Adds an offer to the repository of offers.
/// </summary>
/// <param name="s">Pointer to the Service.</param>
/// <param name = "type">A string, the type of the offer.</param>
/// <param name = "destination">A string, the destination of the offer.</param>
/// <param name = "day">Integer, the day of the departure date.</param>
/// <param name = "month">Integer, the month of the departure date.</param>
/// <param name = "year">Integer, the year of the departure date.</param>
/// <param name = "price">Integer, the price of the offer.</param>
/// <returns>0 - if the offer was sucessfully added; -1 - if the offer could not be added</returns>
int addOfferServ(Service* s, char* type, char* destination, int day, int month, int year, int price);


/// <summary>
/// Removes an offer from the repository of offers.
/// </summary>
/// <param name="s">Pointer to the Service.</param>
/// <param name = "destination">A string, the destination of the offer.</param>
/// <param name = "day">Integer, the day of the departure date.</param>
/// <param name = "month">Integer, the month of the departure date.</param>
/// <param name = "year">Integer, the year of the departure date.</param>
/// <returns>0 - if the offer was sucessfully removed; -1 - if the offer could not be removed</returns>
int removeOfferServ(Service* s, char* destination, int day, int month, int year);


/// <summary>
/// Returns the repository of the Service.
/// </summary>
/// <param name="s">Pointer to the Service.</param>
/// <returns>Pointer to the repository of the Service.</returns>
OffersRepo* getRepo(Service* s);


/// <summary>
/// Undoes the last performed operation.
/// </summary>
/// <param name="s">Pointer to theService.</param>
/// <returns>0, if the undo operation could be done, -1 otherwise.</returns>
int undo(Service* s);


/// <summary>
/// Redoes the last undone operation.
/// </summary>
/// <param name="s">Pointer to the Service.</param>
/// <returns>0, if the redo operation could be done, -1 otherwise.</returns>
int redo(Service* s);


/// <summary>
/// Filters the offers by a given substring that is contained in the destination of the offer and sorts them by the price.
/// </summary>
/// <param name="s">Pointer to the Service.</param>
/// <param name = "substr">A string, the substring to be contained in the destination of the offer.</param>
/// <param name = "result">A string, the result of the filtering.</param>
void filterByDestination(Service* s, char* substr, char* result);


/// <summary>
/// Returns the offers of a given type and after a given date.
/// </summary>
/// <param name="s">Pointer to the Service.</param>
/// <param name = "type">A string, the type of the offer.</param>
/// <param name = "day">Integer, the day of the departure date.</param>
/// <param name = "month">Integer, the month of the departure date.</param>
/// <param name = "year">Integer, the year of the departure date.</param>
/// <param name = "result">A string, the result of the filtering.</param>
void filterByTypeAndDate(Service* s, char* type, int day, int month, int year, char* result);

// Tests
void testsController();

// Extended tests
void extendedTestsController();