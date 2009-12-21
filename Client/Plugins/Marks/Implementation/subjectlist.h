#ifndef SUBJECTLIST_H
#define SUBJECTLIST_H

#include <QWidget>
#include <QListWidget>
#include <QMap>

#include "../../../../Common/TreeDataPlugin.h"
#include "../../../../Common/PluginManager.h"

class SubjectList : public QWidget
{
public:
	SubjectList(PluginManager *pluginManager);
	void	fillClassList();
	QMap<int, QString>	getallclass();

private:
	QListWidget *ClassList;
	TreeDataPlugin	*treePlugin;
};

#endif // SUBJECTLIST_H
