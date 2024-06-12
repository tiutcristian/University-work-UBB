#include <QtWidgets/QApplication>
#include <iostream>
#include <crtdbg.h>
#include "CUI/CUI.h"
#include "GUI/MainWindow.h"
#include "Services/Services.h"
#include "Domain/Domain.h"

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Repository repo("coats.txt");
	Services serv(repo);
	//serv.initializeServ();
	MainWindow w(serv);
	
	w.show();
	return a.exec();
}