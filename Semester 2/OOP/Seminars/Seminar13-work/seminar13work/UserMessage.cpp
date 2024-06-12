#include "UserMessage.h"

Message::Message(std::string message)
{
	this->message = message;
	this->time = std::time(0);
}