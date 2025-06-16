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

class RepositoryExceptions : public std::exception
{
protected:
	std::string message;

public:
	RepositoryExceptions() : std::exception() {}
	RepositoryExceptions(const std::string& msg) : message{ msg } {}
	virtual ~RepositoryExceptions() {}
	virtual const char* what() { return message.c_str(); }
};

class RepositoryDuplicateException : public RepositoryExceptions
{
public:
	const char* what();
};

class RepositoryNotFoundException : public RepositoryExceptions
{
public:
	const char* what();
};

