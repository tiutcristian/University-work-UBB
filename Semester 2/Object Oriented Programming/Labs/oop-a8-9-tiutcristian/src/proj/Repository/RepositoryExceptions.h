#pragma once
#include <exception>
#include <string>

class FileException : public std::exception
{
protected:
	std::string message;

public:
	FileException(const std::string& msg) : message{ msg } {}
	virtual const char* what() { return message.c_str(); }
};

class RepositoryException : public std::exception
{
protected:
	std::string message;

public:
	RepositoryException() : std::exception() {}
	RepositoryException(const std::string& msg) : message{ msg } {}
	virtual ~RepositoryException() {}
	const char* what() const override { return message.c_str(); }
};

class RepositoryDuplicateException : public RepositoryException
{
public:
	RepositoryDuplicateException() : RepositoryException{ 
		"There already exists a coat with the same size and color!" 
	} {}
};

class RepositoryNotFoundException : public RepositoryException
{
public:
	RepositoryNotFoundException() : RepositoryException{ 
		"There is no coat with the given size and color!" 
	} {}
};

