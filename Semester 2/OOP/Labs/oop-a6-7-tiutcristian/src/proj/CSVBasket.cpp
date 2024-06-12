#include "CSVBasket.h"
#include <fstream>
#include "RepositoryExceptions.h"
#include <Windows.h>

void CSVBasket::writeToFile()
{
	ofstream f(this->filename);

	if (!f.is_open())
		throw FileException("The file could not be opened!");

	f << "Size,Color,Price,Quantity,Photo\n";

	for (auto coat : this->shoppingBasket)
		f << coat.getSize() << ','
			<< coat.getColor() << ','
			<< coat.getPrice() << ','
			<< coat.getQuantity() << ','
			<< coat.getPhoto() << '\n';

	f.close();
}

void CSVBasket::displayBasket() const
{
	string aux = "\"" + this->filename + "\"";
	ShellExecuteA(NULL, NULL, aux.c_str(), NULL, NULL, SW_SHOWMAXIMIZED);
}
