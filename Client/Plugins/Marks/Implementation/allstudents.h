#ifndef ALLSTUDENTS_H
#define ALLSTUDENTS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>

#include "../../../../Common/PluginManager.h"

class AllStudents : public QWidget
{
public:
	AllStudents(PluginManager *);
	void	fillList();
	QListWidget		*sList()	{ return _sList; }

private:
	PluginManager	*_pluginManager;
	QListWidget		*_sList;;
};

#endif // ALLSTUDENTS_H
