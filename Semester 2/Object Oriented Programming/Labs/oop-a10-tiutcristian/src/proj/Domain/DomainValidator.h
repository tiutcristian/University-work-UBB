#pragma once
#include <vector>
#include <string>
#include "Domain.h"

class CoatException
{
private:
	std::vector<std::string> errors;

public:
	CoatException(std::vector<std::string> _errors) : errors{ _errors } {}
	std::vector<std::string> getErrors() const { return errors; }
};

class DomainValidator
{
public:
	DomainValidator() {}
	void validate(const Coat& c);
};

