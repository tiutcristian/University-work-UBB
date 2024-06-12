#pragma once
#include <string>
#include <ctime>
class User
{
private:
	std::string uniqueUserName;
	std::string name;
public:
	User(std::string uniqueUserName, std::string name) : uniqueUserName{ uniqueUserName }, name{ name } {}
	std::string getUserName() { return uniqueUserName; }
	std::string getName() { return name; }
};

class Message
{
private:
	std::string message;
	std::time_t time;
public:
	Message(std::string message);
	std::string getText() { return message; }
	std::time_t getTime() { return time; }
};

class UserMessage
{
private:
	User u;
	Message m;
public:
	UserMessage(User u, Message m) : u{ u }, m{ m } {}
	User getUser() { return u; }
	Message getMessage() { return m; }
};

