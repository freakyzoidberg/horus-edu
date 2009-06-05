#ifndef COURSE_H
#define COURSE_H

#include <QtGui/QMainWindow>
#include <QTreeWidget>
#include <QtPlugin>
#include "../../IClientPlugin.h"
#include "../../IDisplayablePlugin.h"
#include "../../INetworkPlugin.h"
#include "../../IFilePlugin.h"

#include "Course_global.h"

namespace Ui
{
    class CourseClass;
}

class COURSESHARED_EXPORT Course : public IClientPlugin, public IDisplayablePlugin, public IFilePlugin
{
    Q_OBJECT
    Q_INTERFACES(IClientPlugin)
    Q_INTERFACES(IDisplayablePlugin)
    Q_INTERFACES(IFilePlugin)

public:
    const QByteArray    getName() const;
    const QByteArray    getVersion() const;
    QStringList         getPluginsConflicts() const;
    QStringList         getPluginsRequired() const;
    QStringList         getPluginsRecommended() const;
    bool                event(QEvent *event);
    QWidget             *getWidget();

private:
    Ui::CourseClass *ui;
    QWidget *fenetre;
    QTreeWidget *tree;
};

#endif // Course_H
