#ifndef VIEWALLMARKS_H
#define VIEWALLMARKS_H

#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QListWidget>
#include <QLabel>
#include <QTableWidget>

#include "../../../../Common/PluginManager.h"
#include "../../../../Common/TreeData.h"
#include "../../../../Common/ExamsData.h"
#include "../../../../Common/MarksData.h"
#include "../../../../Common/MarksDataPlugin.h"
#include "allstudents.h"

class ViewAllMarks : public QWidget
{
	Q_OBJECT
public:
							ViewAllMarks(PluginManager *pluginManager,
										 QTabWidget *mainView);
	QListWidget				*StudentList;

	void					initGradesList(QListWidgetItem *);

	QPushButton				*_add;
	TreeData				*_node;
	QLabel					*_infosLabel;

public slots:
	void	initGradesL(QListWidgetItem *);

private:
	TreeDataPlugin          *td;
	QListWidgetItem			*_item;
	QHBoxLayout				*MainLayout;
	MarksData*				_markData;
	quint32					_studentId;
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
	QTabWidget				*_parent;
	QTableWidget			*mainWidget;
	PluginManager			*_pluginManager;
	AllStudents				*_allS;
};

#endif // VIEWALLMARKS_H
