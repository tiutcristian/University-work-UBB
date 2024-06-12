#include "shoppinglist.h"

shoppinglist::shoppinglist(Basket& basket, QWidget *parent)
    : basket(basket), QWidget(parent)
{
    ui.setupUi(this);
	loadList();
	connectComponents();
}

shoppinglist::~shoppinglist()
{}

void shoppinglist::loadList()
{
	ui.itemsListWidget->clear();
	for (auto item : basket.getItems())
	{
		ui.itemsListWidget->addItem(QString::fromStdString(item));
	}
}

void shoppinglist::connectComponents()
{
	connect(ui.searchLineEdit, &QLineEdit::textChanged, this, &shoppinglist::updateList);
	connect(ui.showButton, &QPushButton::clicked, this, &shoppinglist::showItemsByCategory);
}

void shoppinglist::updateList(const QString& s)
{
	ui.itemsListWidget->clear();
	for (auto item : basket.getItems())
	{
		if (item.find(s.toStdString()) != std::string::npos)
		{
			ui.itemsListWidget->addItem(QString::fromStdString(item));
		}
	}
}

void shoppinglist::showItemsByCategory()
{
	ui.sortedItemsListWidget->clear();
	for (auto item : basket.getItemsByCategory(ui.categoryLineEdit->text().toStdString()))
	{
		ui.sortedItemsListWidget->addItem(QString::fromStdString(item));
	}
}
