#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo repo;
    GUI w(repo);
    w.show();
    return a.exec();
}
