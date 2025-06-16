#include "GUI.h"
#include <QtWidgets/QApplication>
#include <fstream>
#include <string>
#include <QString>
#include <QStringList>
#include <vector>
#include "Department.h"
#include "DepartmentsWindow.h"

std::vector<Department> readFromFile()
{
    std::ifstream fin("departments.txt");
    std::string line;
    std::vector<Department> departments;
    while(getline(fin, line))
	{
		QStringList tokens = QString::fromStdString(line).split("|");
        departments.push_back(Department(tokens[0].trimmed(), tokens[1].trimmed()));
	}
    return departments;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::vector<Department> departments = readFromFile();
    Session session;

    std::vector<GUI*> windows;
    for (auto d : departments)
    {
        GUI* w = new GUI(d, session);
        windows.push_back(w);
        w->show();
    }

    DepartmentsWindow dw(departments, session);
    dw.show();

    a.exec();

    for (auto w : windows)
		delete w;

    return 0;
}
