#include "DomainValidator.h"

void DomainValidator::validate(const Coat& c)
{
	vector<string> errors;
	if (c.getSize() != 'S' && c.getSize() != 'M' && c.getSize() != 'L')
		errors.push_back("The size must be S, M or L!\n");
	if (c.getPrice() <= 0)
		errors.push_back("The price must be a positive number!\n");
	if (c.getQuantity() < 0)
		errors.push_back("The quantity must be a non-negative number!\n");

	size_t posWww = c.getPhoto().find("www");
	size_t posHttp = c.getPhoto().find("http");
	if (posWww != 0 && posHttp != 0)
		errors.push_back("The photo link must start with one of the following strings: \"www\" or \"http\"");

	if (errors.size() > 0)
		throw CoatException(errors);
}