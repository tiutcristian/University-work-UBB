#include "shoppinglist.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Basket basket;
    shoppinglist w(basket);
    w.show();
    return a.exec();
}
