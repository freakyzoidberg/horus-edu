#include <QtCore/qplugin.h>
#include <QDebug>
#include <QtXml/QXmlSimpleReader>
#include <QFile>
#include <QFrame>

#include "../../../../Common/PluginManager.h"
#include "../../../../Common/FileDataPlugin.h"
#include "../../../../Common/FileData.h"

#include "LessonModel_ext.h"
#include "LessonManager.h"

bool	LessonManager::canLoad() const
{
	if (pluginManager->findPlugin<TreeDataPlugin *>("Tree Data Base") && pluginManager->findPlugin<FileDataPlugin *>("File Data Base"))
        return (true);
    return (false);
}

void    LessonManager::load()
{
	lessonModel = new LessonModel_ext(pluginManager);
}

void    LessonManager::unload()
{
    delete lessonModel;
}

const QString	LessonManager::pluginName() const
{
	return ("LessonManager");
}

const QString	LessonManager::pluginVersion() const
{
	return ("1.1");
}

LessonModel* LessonManager::getLessonModel()
{
    return lessonModel;
}
