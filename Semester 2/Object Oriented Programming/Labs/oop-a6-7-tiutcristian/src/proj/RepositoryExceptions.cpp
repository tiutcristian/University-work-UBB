#include "RepositoryExceptions.h"

const char* RepositoryDuplicateException::what()
{
	return "There already exists a coat with the same size and color!";
}

const char* RepositoryNotFoundException::what()
{
	return "There is no coat with the given size and color!";
}
