#pragma once
#include <vector>
#include <QString>

class Doc
{
private:
	QString name;
	std::vector<QString> keywords;
	QString content;

public:
	Doc(QString name, std::vector<QString> keywords, QString content)
		: name(name), keywords(keywords), content(content) {}

	QString getName() { return name; }
	std::vector<QString> getKeywords() { return keywords; }
	QString getContent() { return content; }

	void setName(QString name) { this->name = name; }
	void setKeywords(std::vector<QString> keywords) { this->keywords = keywords; }
	void setContent(QString content) { this->content = content; }

	QString toString();
};

