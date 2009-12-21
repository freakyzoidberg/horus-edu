#ifndef SUBJECTLIST_H
#define SUBJECTLIST_H

#include <QWidget>
#include <QListWidget>
#include <QMap>
#include <QLineEdit>

#include "../../../../Common/TreeDataPlugin.h"
#include "../../../../Common/PluginManager.h"

class SubjectList : public QWidget
{
	Q_OBJECT

public:
	SubjectList(PluginManager *pluginManager);
	void	fillSubjectList();
	QMap<int, QString>	getallsubject();

private slots:
	void showExams(QListWidgetItem *);
	void addAnExam();

private:
	QListWidget		*SubjectsList;
	TreeDataPlugin	*treePlugin;
	PluginManager	*_pluginManager;
	QLineEdit   *examComment;
};

#endif // SUBJECTLIST_H
