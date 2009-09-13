#ifndef ILESSONMANAGER_H
#define ILESSONMANAGER_H

#include "LessonModel.h"

//! Interface of the plugin ILessonManager
/*!
    This interface describes the methods used in the plugin to load a representation
    of a lesson as well as save a lesson or create a new lesson.
*/
class ILessonManager
{
    public:
        virtual LessonModel* getLessonModel() = 0;
};

Q_DECLARE_INTERFACE(ILessonManager, "net.horus.Client.LessonManagerInterface/1.0");

#endif // ILESSONMANAGER_H
