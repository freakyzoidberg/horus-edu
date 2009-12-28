#ifndef MARKSMANAGER_H
#define MARKSMANAGER_H

#include "../../../../Common/PluginManager.h"
#include "../../../../Common/TreeDataPlugin.h"
#include "../../../../Common/ExamsDataPlugin.h"
#include "InfoPanel.h"
#include "ClassList.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>

class MarksManager : public QWidget
{
public:
	MarksManager(PluginManager *);
	QListWidget				*StudentList;

public slots:
	void                  classSelected(QListWidgetItem *);
	void                  goadd();
	void                  godelete();
	void           goedit();
	void                                    goreset();
	void                                    gook();
	void									fallback();

private:
	TreeDataPlugin          *td;
	QHBoxLayout				*MainLayout;
	ClassList *				_classList;
	//AdmListEdt				*_admEDTList;
	QFrame					*informationsFrame;
	QVBoxLayout				*informationsLayout;
	InfoPanel				*infos;
	QPushButton				*del;
	QPushButton				*edit;
	QPushButton				*ok;
	QPushButton				*save;
	QPushButton				*reset;
	QPushButton				*back;
	QPushButton				*add;
	PluginManager			 *_pm;
};

#endif // MARKSMANAGER_H
