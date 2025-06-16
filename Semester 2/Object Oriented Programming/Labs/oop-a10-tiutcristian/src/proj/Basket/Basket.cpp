#include "Basket.h"
#include <cassert>

int Basket::findCoat(char size, const std::string& color)
{
	auto it = std::find_if(this->shoppingBasket.begin(), this->shoppingBasket.end(), [size, color](const Coat& coat) { return coat.getSize() == size && coat.getColor() == color; });
	if (it != this->shoppingBasket.end())
		return (int)std::distance(this->shoppingBasket.begin(), it);
	return -1;
}

int Basket::rowCount(const QModelIndex& parent) const
{
	return this->shoppingBasket.size();
}

int Basket::columnCount(const QModelIndex& parent) const
{
	return 5;
}

QVariant Basket::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();
	Coat coat = this->shoppingBasket[row];
	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(std::string(1, coat.getSize()));
		case 1:
			return QString::fromStdString(coat.getColor());
		case 2:
			return QString::fromStdString(std::to_string(coat.getPrice()));
		case 3:
			return QString::fromStdString(std::to_string(coat.getQuantity()));
		case 4:
			return QString::fromStdString(coat.getPhoto());
		default:
			break;
		}
	}
	return QVariant();
}

QVariant Basket::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return "Size";
			case 1:
				return "Color";
			case 2:
				return "Price";
			case 3:
				return "Quantity";
			case 4:
				return "Photo";
			default:
				break;
			}
		}
	}
	return QVariant();
}

void Basket::addCoat(const Coat& coat)
{
	int pos = this->findCoat(coat.getSize(), coat.getColor());
	if (pos != -1)
		this->shoppingBasket[pos].setQuantity(this->shoppingBasket[pos].getQuantity() + coat.getQuantity());
	else
		this->shoppingBasket.push_back(coat);
}

std::string Basket::toString()
{
	std::string allElements = "";
	for (auto coat : this->shoppingBasket)
	{
		std::string crt = coat.toString();
		allElements += crt;
		allElements += "\n";
	}
	return allElements;
}

void Basket::testBasket()
{
	Basket basket;
	assert(basket.findCoat('M', "red") == -1);
	basket.addCoat(Coat{ 'M', "red", 100, 10, "photo1" });
	assert(basket.findCoat('M', "red") == 0);
	basket.addCoat(Coat{ 'L', "blue", 200, 20, "photo2" });
	assert(basket.findCoat('L', "blue") == 1);
	basket.addCoat(Coat{ 'S', "green", 300, 30, "photo3" });
	assert(basket.findCoat('S', "green") == 2);
	basket.addCoat(Coat{ 'M', "yellow", 400, 40, "photo4" });
	assert(basket.findCoat('M', "yellow") == 3);
	basket.addCoat(Coat{ 'L', "black", 500, 50, "photo5" });
	assert(basket.findCoat('L', "black") == 4);
	basket.addCoat(Coat{ 'M', "red", 600, 60, "photo6" });
	assert(basket.shoppingBasket[0].getQuantity() == 70);
	assert(basket.shoppingBasket[1].getQuantity() == 20);
	assert(basket.shoppingBasket[2].getQuantity() == 30);
	assert(basket.shoppingBasket[3].getQuantity() == 40);
	assert(basket.shoppingBasket[4].getQuantity() == 50);
	assert(basket.shoppingBasket[0].getPrice() == 100);
	assert(basket.shoppingBasket[1].getPrice() == 200);
	assert(basket.shoppingBasket[2].getPrice() == 300);
	assert(basket.shoppingBasket[3].getPrice() == 400);
	assert(basket.shoppingBasket[4].getPrice() == 500);
	assert(basket.shoppingBasket[0].getPhoto() == "photo1");
	assert(basket.shoppingBasket[1].getPhoto() == "photo2");
	assert(basket.shoppingBasket[2].getPhoto() == "photo3");
	assert(basket.shoppingBasket[3].getPhoto() == "photo4");
	assert(basket.shoppingBasket[4].getPhoto() == "photo5");
	assert(basket.toString() ==
		"M red 100.000000 70 photo1\n"
		"L blue 200.000000 20 photo2\n"
		"S green 300.000000 30 photo3\n"
		"M yellow 400.000000 40 photo4\n"
		"L black 500.000000 50 photo5\n");
}
