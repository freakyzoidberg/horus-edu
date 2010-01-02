#ifndef STUDENTSLIST_H
#define STUDENTSLIST_H

#include <QWidget>
#include <QListWidget>
#include "../../../../Common/TreeData.h"
#include "../../../../Common/PluginManager.h"

class StudentsList : public QWidget
{
public:
					StudentsList(TreeData *node,
								 PluginManager *pluginManager);
	QListWidget		*_sList;
	void			fillStudentList();
	void			setNode(TreeData *node)		{ _node = node; }

public slots:
	void			studentSelection(QListWidgetItem *);

private:
	PluginManager	*_pluginManager;
	TreeData		*_node;
};

#endif // STUDENTSLIST_H
