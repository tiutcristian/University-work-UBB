#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


UI* createUI(Service* s)
{
	UI* ui = malloc(sizeof(UI));
	if (ui == NULL)
		return NULL;
	ui->serv = s;
	return ui;
}

void destroyUI(UI* ui)
{
	destroyService(ui->serv);
	free(ui);
}

/// <summary>
/// Prints the menu.
/// </summary>
void printMenu()
{
	printf("1. Add offer\n");
	printf("2. Delete offer\n");
	printf("3. Update offer\n");
	printf("4. Show offers containing substring\n");
	printf("5. Show offers of a given type, having departure after a given date\n");
	printf("6. Undo\n");
	printf("7. Redo\n");
	printf("0. Exit\n");
}


/// <summary>
/// Verifies if the given command is valid (is either 1, 2, 3or 0)
/// </summary>
/// <param name="command">- integer</param>
/// <returns>1 - if the command is valid, 0 - otherwise</returns>
int validCommand(int command)
{
	if (command >= 0 && command <= 7)
		return 1;
	return 0;
}


/// <summary>
/// Reads an integer number from the keyboard. Asks for number while read errors encoutered.
/// </summary>
/// <param name="message">- the message to be displayed when asking the user for input.</param>
/// <returns>the number.</returns>
int readIntegerNumber(const char* message)
{
	char s[16];
	int res = 0;
	int flag = 0;
	int r = 0;

	while (flag == 0)
	{
		printf(message);
		scanf("%s", s);

		r = sscanf(s, "%d", &res);	// reads data from s and stores them as integer, if possible; returns 1 if successful
		flag = (r == 1);
		if (flag == 0)
			printf("Error reading number!\n");
	}
	return res;
}


/// <summary>
/// Reads a string with spaces from the standard input.
/// </summary>
/// <param name="message">- string, message to be shown to the user.</param>
/// <param name="maxStrSize">- integer, the maximum size for the string to be read</param>
/// <param name="str">- the string that was read.</param>
void readStringWithSpaces(const char* message, int maxStrSize, char str[])
{
	printf(message);
	fgets(str, maxStrSize, stdin);
	// the newline is also read so we must eliminate it from the string
	size_t size = strlen(str) - 1;
	if (str[size] == '\n')
		str[size] = '\0';
}


/// <summary>
/// Reads an offer from the console.
/// </summary>
/// <param name="ui">- pointer to the UI.</param>
/// <returns>0 if the offer was added successfully and -1 otherwise</returns>
int addOfferUI(UI* ui)
{
	char type[11], destination[100];
	int day, month, year, price;

	fgetc(stdin);
	readStringWithSpaces("Please input the type: ", 11, type);
	if (strcmp(type, "city break") != 0 &&
		strcmp(type, "mountain") != 0 &&
		strcmp(type, "seaside") != 0)
	{
		printf("Invalid type\n");
		return -1;
	}
	readStringWithSpaces("Please input the destination: ", 100, destination);
	day = readIntegerNumber("Please input the departure day: ");
	if (day < 1 || day > 31)
	{
		printf("Invalid day\n");
		return -1;
	}
	month = readIntegerNumber("Please input the departure month: ");
	if (month < 1 || month > 12)
	{
		printf("Invalid month\n");
		return -1;
	}
	year = readIntegerNumber("Please input the departure year: ");
	if (year < 2024)
	{
		printf("Invalid year\n");
		return -1;
	}
	price = readIntegerNumber("Please input the price: ");
	if (price < 0)
	{
		printf("Invalid price\n");
		return -1;
	}

	return addOfferServ(ui->serv, type, destination, day, month, year, price);
}


/// <summary>
/// Deletes an offer.
/// </summary>
/// <param name="ui">- pointer to the UI.</param>
/// <returns>0 if the offer was deleted successfully and -1 otherwise</returns>
int deleteOfferUI(UI* ui)
{
	char destination[100];
	int day, month, year;

	fgetc(stdin);
	readStringWithSpaces("Please input the destination: ", 100, destination);
	day = readIntegerNumber("Please input the departure day: ");
	if (day < 1 || day > 31)
	{
		printf("Invalid day\n");
		return -1;
	}
	month = readIntegerNumber("Please input the departure month: ");
	if (month < 1 || month > 12)
	{
		printf("Invalid month\n");
		return -1;
	}
	year = readIntegerNumber("Please input the departure year: ");
	if (year < 2024)
	{
		printf("Invalid year\n");
		return -1;
	}

	return removeOfferServ(ui->serv, destination, day, month, year);
}


/// <summary>
/// Updates an offer.
/// </summary>
/// <param name="ui">- pointer to the UI.</param>
/// <returns>0 if the offer was updated successfully and -1 otherwise</returns>
int updateOfferUI(UI* ui)
{
	char type[11], oldDestination[100], newDestination[100];
	int newDay, newMonth, newYear, day, month, year, price, res;

	fgetc(stdin);
	readStringWithSpaces("Please input the old destination: ", 100, oldDestination);
	day = readIntegerNumber("Please input the old departure day: ");
	if (day < 1 || day > 31)
	{
		printf("Invalid day\n");
		return -1;
	}
	month = readIntegerNumber("Please input the old departure month: ");
	if (month < 1 || month > 12)
	{
		printf("Invalid month\n");
		return -1;
	}
	year = readIntegerNumber("Please input the old departure year: ");
	if (year < 2024)
	{
		printf("Invalid year\n");
		return -1;
	}
	res = removeOfferServ(ui->serv, oldDestination, day, month, year);
	if (res == -1)
		return -1;

	fgetc(stdin);
	readStringWithSpaces("Please input the new type: ", 11, type);
	if (strcmp(type, "city break") != 0 &&
		strcmp(type, "mountain") != 0 &&
		strcmp(type, "seaside") != 0)
	{
		printf("Invalid type\n");
		return -1;
	}
	readStringWithSpaces("Please input the new destination: ", 100, newDestination);
	newDay = readIntegerNumber("Please input the new departure day: ");
	if (newDay < 1 || newDay > 31)
	{
		printf("Invalid day\n");
		return -1;
	}
	newMonth = readIntegerNumber("Please input the new departure month: ");
	if (newMonth < 1 || newMonth > 12)
	{
		printf("Invalid month\n");
		return -1;
	}
	newYear = readIntegerNumber("Please input the new departure year: ");
	if (newYear < 2024)
	{
		printf("Invalid year\n");
		return -1;
	}
	price = readIntegerNumber("Please input the new price: ");
	if (price < 0)
	{
		printf("Invalid price\n");
		return -1;
	}

	return addOfferServ(ui->serv, type, newDestination, newDay, newMonth, newYear, price);
}


/// <summary>
/// Prints the offers that contain a given substring in their destination, sorted by price.
/// </summary>
/// <param name="ui">- pointer to the UI.</param>
int showOffersContainingSubstring(UI* ui)
{
	char str[100];
	printf("Enter a string: ");
	fgetc(stdin);
	fgets(str, 100, stdin);
	str[strlen(str) - 1] = '\0';
	/*char result[1000];
	if (result == NULL)
		return -1;*/
	//filterByDestination(ui->serv, str, result);
	char tmp[200];
	for (int i = 0; i < ui->serv->repo->offers->length; i++)
	{
		offerToString((Offer*)get(ui->serv->repo->offers, i), tmp);
		printf("%s\n", tmp);
	}
		
	return 0;
}


/// <summary>
/// Prints the offers of a given type and after a given date.
/// </summary
/// <param name="ui">- pointer to the UI.</param>
/// <returns>0 if the offers were printed successfully and -1 otherwise</returns>
int showOffersOfType(UI* ui)
{
	char type[11];
	int day, month, year;
	printf("Type: ");
	fgetc(stdin);
	fgets(type, 11, stdin);
	type[strlen(type) - 1] = '\0';
	if (strcmp(type, "city break") != 0 &&
		strcmp(type, "mountain") != 0 &&
		strcmp(type, "seaside") != 0)
	{
		printf("Invalid type\n");
		return -1;
	}

	day = readIntegerNumber("Day: ");
	if (day < 1 || day > 31)
	{
		printf("Invalid day\n");
		return -1;
	}

	month = readIntegerNumber("Month: ");
	if (month < 1 || month > 12)
	{
		printf("Invalid month\n");
		return -1;
	}

	year = readIntegerNumber("Year: ");
	if (year < 2024)
	{
		printf("Invalid year\n");
		return -1;
	}

	char* result = malloc(getRepoLength(getRepo(ui->serv)) * 100 * sizeof(char));
	if (result == NULL)
		return -1;
	filterByTypeAndDate(ui->serv, type, day, month, year, result);
	printf("%s", result);
	free(result);
	return 0;
}


void startUI(UI* ui)
{
	while (1)
	{
		printMenu();
		int command = readIntegerNumber("Input command: ");
		while (validCommand(command) == 0)
		{
			printf("Please input a valid command!\n");
			command = readIntegerNumber("Input command: ");
		}
		if (command == 0) {
			printf("Exiting...\n");
			break;
		}
		switch (command)
		{
		case 1:
		{
			int res = addOfferUI(ui);
			if (res == 0)
				printf("Offer added successfully.\n");
			else
				printf("Error! Offer could not be added!\n");
			break;
		}
		case 2:
		{
			int res = deleteOfferUI(ui);
			if (res == 0)
				printf("Offer deleted successfully.\n");
			else
				printf("Error! Offer could not be deleted!\n");
			break;
		}
		case 3:
		{
			int res = updateOfferUI(ui);
			if (res == 0)
				printf("Offer updated successfully.\n");
			else
				printf("Error! Offer could not be updated!\n");
			break;
		}
		case 4:
		{
			int res = showOffersContainingSubstring(ui);
			if (res == -1)
				printf("Error! Memory could not be allocated!\n");
			break;
		}
		case 5:
		{
			int res = showOffersOfType(ui);
			if (res == -1)
				printf("Error! Memory could not be allocated!\n");
			break;
		}
		case 6:
		{
			int res = undo(ui->serv);
			if (res == 0)
				printf("Undo was successful.\n");
			else
				printf("No more undos to be made.\n");
			break;
		}
		case 7:
		{
			int res = redo(ui->serv);
			if (res == 0)
				printf("Redo was successful.\n");
			else
				printf("No more redos to be made.\n");
			break;
		}
		}
	}
}
