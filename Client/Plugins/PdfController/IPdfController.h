#ifndef IPDFCONTROLLER_H
#define IPDFCONTROLLER_H

#include <QtGui/QStylePlugin>
#include <QList>

#include "../../LessonManager/ILesson.h"

class IPdfController
{
    public:
        virtual void    setObject(ILesson::IPage::IObject *object) = 0;
        virtual const QList<ILesson::IPage::IObject *> &    getObjects() = 0;
};

#endif // IPDFCONTROLLER_H
