#ifndef MARKSEXAMSLIST_H
#define MARKSEXAMSLIST_H

#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QListWidget>
#include <QLabel>
#include "../../../../Common/PluginManager.h"
#include "../../../../Common/TreeData.h"
#include "../../../../Common/ExamsData.h"
#include "newexams.h"

#include "examslist.h"

class MarksExamsList : public QWidget
{
	Q_OBJECT
public:
	MarksExamsList(PluginManager *, QTabWidget *);
	QListWidget				*StudentList;

	ExamsList	*examsList() { return _examsList; }
	QPushButton				*_add;
	TreeData				*_node;
	NewExams				*_formAdd;


public slots:
	void	addExam();
	void	saveExam();
	void	fallback();
private:
	TreeDataPlugin          *td;
	QHBoxLayout				*MainLayout;
	ExamsList *				_examsList;
	//AdmListEdt			*_admEDTList;
	QFrame					*informationsFrame;
	QVBoxLayout				*informationsLayout;
	//InfoPanel				*infos;
	QPushButton				*del;
	QPushButton				*edit;
	QPushButton				*ok;
	QPushButton				*save;
	QPushButton				*reset;
	QPushButton				*back;


private:
	QTabWidget		*_parent;
	PluginManager	*_pluginManager;
};

#endif // MARKSEXAMSLIST_H
