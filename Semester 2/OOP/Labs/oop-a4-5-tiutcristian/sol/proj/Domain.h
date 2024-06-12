#pragma once
#include <string>
using namespace std;

class Coat
{
private:
	char size;
	string colour;
	double price;
	int quantity;	
	string photo;

public:
	/// <summary>
	/// Creates a coat with the default parameters
	/// </summary>
	Coat();

	/// <summary>
	/// Creates a coat with the given parameters
	/// </summary>
	/// <param name="size">The size of the coat</param>
	/// <param name="colour">The colour of the coat</param>
	/// <param name="price">The price of the coat</param>
	/// <param name="quantity">The quantity of the coat</param>
	/// <param name="photo">The photo of the coat</param>
	Coat(char size, string colour, double price, int quantity, string photo);

	/// <summary>
	/// Returns the coat as a string
	/// </summary>
	string toString();

	/// <summary>
	/// Overloads the == operator
	/// </summary>
	/// <param name="c">The coat to compare to</param>
	/// <returns>True if the coats are equal, false otherwise</returns>
	bool operator==(const Coat& c);


	// Getters

	char getSize() const;
	string getColor() const;
	double getPrice() const;
	int getQuantity() const;
	string getPhoto() const;


	// Setters

	void setSize(char size);
	void setColour(string colour);
	void setPrice(double price);
	void setQuantity(int quantity);
	void setPhoto(string photo);

	// Tests
	static void testCoat();
};
