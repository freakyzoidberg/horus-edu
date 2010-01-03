#ifndef STUDENTSLIST_H
#define STUDENTSLIST_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include "../../../../Common/TreeData.h"
#include "../../../../Common/PluginManager.h"
#include "../../../../Common/ExamsDataPlugin.h"
#include "../../../../Common/ExamsData.h"

class StudentsList : public QWidget
{
public:
					StudentsList(TreeData *node,
								 PluginManager *pluginManager,
								 QVBoxLayout *RightLayout);
	QListWidget		*_sList;
	void			fillStudentList();
	void			setNode(TreeData *node)		{ _node = node; }
	void			setItem(QListWidgetItem *item) { _item = item; }

public slots:


private:
	PluginManager	*_pluginManager;
	TreeData		*_node;
	ExamsData		*_exam;
	QListWidgetItem *_item;
};

#endif // STUDENTSLIST_H
