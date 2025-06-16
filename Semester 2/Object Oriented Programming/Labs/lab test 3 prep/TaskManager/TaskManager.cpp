#include "TaskManager.h"

TaskManager::TaskManager(Repo* repo, QWidget *parent)
    : QWidget(parent), repo(repo)
{
    ui.setupUi(this);
    ui.tasksList->setModel(repo);
	connect(ui.showButton, &QPushButton::clicked, [this, repo]() {
		std::string str = ui.priorityLineEdit->text().toStdString();
		MySortFilterProxyModel* proxyModel = new MySortFilterProxyModel(str);
		proxyModel->setSourceModel(repo);
		ui.tasksList->setModel(proxyModel);
		if (str == "")
			ui.totalDurationLabel->setText("");
		else
		{
			int totalDuration = 0;
			for (int i = 0; i < repo->rowCount(); i++)
				if (proxyModel->filterAcceptsRow(i, QModelIndex()))
					totalDuration += repo->data(repo->index(i, 0)).toString().split("|")[1].toInt();
			ui.totalDurationLabel->setText("Total duration: " + QString::number(totalDuration));
		}
	});	
}

TaskManager::~TaskManager()
{}

bool MySortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
	QModelIndex index = sourceModel()->index(source_row, 0, source_parent);
	QStringList tokens = sourceModel()->data(index).toString().split("|");
	return str == "" || tokens[2] == QString::fromStdString(str);
}