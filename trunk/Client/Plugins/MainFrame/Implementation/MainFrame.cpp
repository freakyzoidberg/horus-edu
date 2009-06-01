#include "MainFrame.h"

#include <QDebug>

Q_EXPORT_PLUGIN2(MainFrame, MainFrame)

MainFrame::MainFrame()
{
}

const QByteArray    MainFrame::getName() const
{
    return ("MainFrame");
}

const QByteArray    MainFrame::getVersion() const
{
    return ("0.1");
}

QStringList         MainFrame::getPluginsRequired() const
{
    return (QStringList());
}

QStringList         MainFrame::getPluginsConflicts() const
{
    return (QStringList());
}

QStringList         MainFrame::getPluginsRecommended() const
{
    return (QStringList());
}

bool                MainFrame::event(QEvent *event)
{
    qDebug() << "MainFrame: Received Event not managed" << event;
    return (false);
}
