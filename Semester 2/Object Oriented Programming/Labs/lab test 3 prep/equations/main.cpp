#include "gui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo* repo = new Repo();
    gui w(repo);
    w.show();
    return a.exec();
}
