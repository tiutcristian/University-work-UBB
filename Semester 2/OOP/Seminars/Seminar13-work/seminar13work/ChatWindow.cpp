#include "ChatWindow.h"

ChatWindow::ChatWindow(std::string username, std::string name, 
	ChatSession& chatSession, QWidget *parent)
	: QWidget(parent), chatSession(chatSession)
{
	ui.setupUi(this);
	this->user = new User(username, name);
	connect(ui.sendButton, &QPushButton::clicked, this, &ChatWindow::sendMessage);
	this->chatSession.registerObserver(this);
}

ChatWindow::~ChatWindow()
{}

void ChatWindow::update()
{
	ui.listWidget->clear();
	std::vector<UserMessage*> messages = chatSession.getMessages();
	for (auto m : messages)
	{
		QListWidgetItem* item = new QListWidgetItem(
			"[" + QString::fromStdString(m->getUser().getName()) + "]" +
			QString::fromStdString(m->getMessage().getText())
		);
		if (m->getUser().getUserName() == user->getUserName())
			item->setTextAlignment(Qt::AlignRight);
		else
			item->setTextAlignment(Qt::AlignLeft);
		ui.listWidget->addItem(item);
	}
}

void ChatWindow::sendMessage()
{
	QString message = ui.lineEdit->text();
	if (message.isEmpty())
		return;
	Message m(message.toStdString());
	chatSession.addMessage(*user, m);
	ui.lineEdit->clear();
	this->chatSession.notify();
}
