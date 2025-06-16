#pragma once
#include "Basket.h"

class FileBasket : public Basket
{
protected:
	std::string filename;

public:
	FileBasket(const std::string& filename) : filename{ filename } {}
	void setFileName(const std::string& filename) { this->filename = filename; }
	virtual void writeToFile() = 0;
	virtual void displayBasket() const = 0;
};

