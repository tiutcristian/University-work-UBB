#pragma once
#include "FileBasket.h"

class HTMLBasket : public FileBasket
{
public:
	HTMLBasket(const std::string& filename) : FileBasket(filename) {}

	void writeToFile() override;
	void displayBasket() const override;
};

