#include "Doc.h"

QString Doc::toString()
{
	QString str = name + " | ";
	for (int i = 0; i < keywords.size(); i++)
	{
		str += keywords[i];
		if (i < keywords.size() - 1)
			str += ", ";
	}
	return str;
}
