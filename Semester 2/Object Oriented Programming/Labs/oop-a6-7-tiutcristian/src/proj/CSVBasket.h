#pragma once
#include "FileBasket.h"

class CSVBasket : public FileBasket
{
public:
	CSVBasket(const std::string& filename) : FileBasket(filename) {}
	void writeToFile() override;
	void displayBasket() const override;
};

