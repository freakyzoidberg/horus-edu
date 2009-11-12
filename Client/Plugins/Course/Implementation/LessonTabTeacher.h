#ifndef LESSONTABTEACHER_H
#define LESSONTABTEACHER_H

#include <QWidget>

#include "../../../../Common/PluginManager.h"

class LessonTabTeacher : public QWidget
{
public:
	LessonTabTeacher(PluginManager *pluginManager);

private:
	PluginManager *_pluginManager;
};

#endif // LESSONTABTEACHER_H
