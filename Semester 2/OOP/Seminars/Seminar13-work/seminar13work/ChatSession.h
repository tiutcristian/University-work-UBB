#pragma once
#include "Subject.h"
#include "UserMessage.h"

class ChatSession : public Subject
{
private:
	std::vector<UserMessage*> messages;
public:
	void addMessage(User u, Message m);
	std::vector<UserMessage*> getMessages();
};