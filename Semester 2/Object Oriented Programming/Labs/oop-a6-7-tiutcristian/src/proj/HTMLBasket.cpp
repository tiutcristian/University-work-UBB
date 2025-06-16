#include "HTMLBasket.h"
#include <fstream>
#include "RepositoryExceptions.h"
#include <Windows.h>

void HTMLBasket::writeToFile()
{
	std::ofstream file(this->filename);
	if (!file.is_open())
		throw FileException("The file could not be opened!");

	file << "<!DOCTYPE html>  ";
	file << "<html> ";
	file << "<head> ";
	file << "    <title>Playlist</title>";
	file << "</head> ";
	file << "<body> ";
	file << "<table border=\"1\">";
	file << "    <tr> ";
	file << "        <td>Size</td>";
	file << "        <td>Color</td>";
	file << "        <td>Price</td>";
	file << "        <td>Quantity</td>";
	file << "        <td>Photo link</td>";
	file << "    </tr>";
	for (auto s : this->shoppingBasket)
	{
		file << "    <tr>";
		file << "        <td>" << s.getSize() << "</td>";
		file << "        <td>" << s.getColor() << "</td>";
		file << "        <td>" << s.getPrice() << "</td>";
		file << "        <td>" << s.getQuantity() << "</td>";
		file << "        <td><a href=\"" << s.getPhoto() << "\">Link</a></td>";
		file << "    </tr>";
	}
	file << "</table>";
	file << "</body>";
	file << "</html>";

	file.close();
}

void HTMLBasket::displayBasket() const
{
	std::string aux = "\"" + this->filename + "\"";
	ShellExecuteA(NULL, NULL, aux.c_str(), NULL, NULL, SW_SHOWMAXIMIZED);
}
