#include "GUI.h"
#include <QMessageBox>

GUI::GUI(Repo repo, QWidget *parent)
    : repo(repo), QWidget(parent)
{
    ui.setupUi(this);
	populateList();
	connectComponents();
}

GUI::~GUI()
{}

void GUI::connectComponents()
{
    connect(ui.searchLineEdit, &QLineEdit::textChanged, this, &GUI::populateList);
	connect(ui.showButton, &QPushButton::clicked, this, &GUI::getBestMatch);
}

void GUI::populateList()
{
    ui.docList->clear();
	QString str = ui.searchLineEdit->text();
	std::vector<Doc> docs = repo.getDocs(str);
	for (auto doc : docs)
	{
		QListWidgetItem* item = new QListWidgetItem(doc.toString());
		ui.docList->addItem(item);
	}
}

void GUI::getBestMatch()
{
	QString str = ui.searchLineEdit->text();
	try
	{
		Doc doc = repo.bestMatch(str);
		ui.docList->clear();
		QListWidgetItem* item = new QListWidgetItem(doc.toString());
		ui.docList->addItem(item);
	}
	catch (const std::exception& e)
	{
		QMessageBox::warning(this, "Warning", e.what());
	}
}
