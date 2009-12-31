#ifndef EXAMSLIST_H
#define EXAMSLIST_H

#include <QWidget>
#include <QListWidget>
#include <QMap>
#include <QLineEdit>

#include "../../../Common/PluginManager.h"
#include "../../../Common/TreeDataPlugin.h"
#include "../../../Common/ExamsDataPlugin.h"

class ExamsList : public QWidget
{

	Q_OBJECT
public:
	ExamsList(PluginManager *pluginManager);
	void	fillExamsList();
	QMap<int, QString>	getallexams();
	QMap<int, QString>  Exams(quint32 userId);
	QMap<int, QString>  Exams(TreeData *node);

private slots:
	void showExams(QListWidgetItem *);
	void addAnExam();

private:
	QListWidget		*_examsList;
	TreeDataPlugin	*treePlugin;
	ExamsDataPlugin	*examsPlugin;
	PluginManager	*_pluginManager;
	QLineEdit		*examComment;
};

#endif // EXAMSLIST_H
