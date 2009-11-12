#ifndef LESSONTABSTUDENT_H
#define LESSONTABSTUDENT_H

#include <QWidget>

#include "../../../../Common/PluginManager.h"

class LessonTabStudent : public QWidget
{
public:
	LessonTabStudent(PluginManager *pluginManager);

private:
	PluginManager	*_pluginManager;
};

#endif // LESSONTABSTUDENT_H
