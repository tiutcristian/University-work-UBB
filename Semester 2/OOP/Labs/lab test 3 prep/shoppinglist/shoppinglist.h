#pragma once

#include <QtWidgets/QWidget>
#include "ui_shoppinglist.h"
#include "Basket.h"

class shoppinglist : public QWidget
{
    Q_OBJECT

public:
    shoppinglist(Basket& basket, QWidget *parent = nullptr);
    ~shoppinglist();

private:
    Ui::shoppinglistClass ui;
    Basket& basket;

    void loadList();
    void connectComponents();
    void updateList(const QString& s);
    void showItemsByCategory();
};
