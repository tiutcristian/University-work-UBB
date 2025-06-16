#include "ChatSession.h"

void ChatSession::addMessage(User u, Message m)
{
	messages.push_back(new UserMessage(u, m));
}

std::vector<UserMessage*> ChatSession::getMessages()
{
	return messages;
}
