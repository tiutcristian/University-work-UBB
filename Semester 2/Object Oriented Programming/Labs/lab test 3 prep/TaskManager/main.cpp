#include "TaskManager.h"
#include <QtWidgets/QApplication>
#include "Repo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo* repo = new Repo();
    TaskManager w(repo);
    w.show();
    return a.exec();
}
