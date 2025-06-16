#pragma once
#include <vector>
#include "../Domain/Domain.h"

class Repository
{
private:
	std::vector<Coat> coats;
	void saveToFile();
	void loadFromFile();
	std::string filename;

public:
	Repository(const std::string& filename = "tmp.txt");

	Repository(const Repository& repository) : coats(repository.coats) {}

	inline Coat& operator[](int pos) { return this->coats[pos]; }

	int getSize() const { return (int)this->coats.size(); }

	void addCoat(const Coat& c);

	void updateCoat(const Coat& oldCoat, const Coat& newCoat);

	void deleteCoat(const Coat& c);

	std::vector<Coat>::iterator findCoatIt(char size, const std::string& color);

	Coat* findCoatPtr(char size, const std::string& color) { return &*this->findCoatIt(size, color); }

	Coat findCoat(char size, const std::string& color) { return *this->findCoatPtr(size, color); }

	Repository filterBySize(char size);

	void decrementQuantity(char size, const std::string& color);

	std::string toString();

	std::vector<Coat> getElements() { return this->coats; }

	int getQuantityBySize(char size);

	static void testRepository();
	
	void clearRepo() { this->coats.clear(); }

	~Repository();
};
