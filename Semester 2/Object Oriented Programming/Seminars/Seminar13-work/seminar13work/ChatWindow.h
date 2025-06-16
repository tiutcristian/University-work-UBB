#pragma once

#include <QWidget>
#include "ui_ChatWindow.h"
#include "Observer.h"
#include "ChatSession.h"

class ChatWindow : public QWidget, public Observer
{
	Q_OBJECT

public:
	ChatWindow(std::string username, std::string name, 
		ChatSession& chatSession, QWidget *parent = nullptr);
	~ChatWindow();
	void update() override;
	void sendMessage();

private:
	Ui::ChatWindowClass ui;
	User* user;
	ChatSession& chatSession;
};
