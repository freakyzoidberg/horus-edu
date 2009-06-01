#include "MainFrame.h"


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
    return (NULL);
}

QStringList         MainFrame::getPluginsConflicts() const
{
    return (NULL);
}

QStringList         MainFrame::getPluginsRecommended() const
{
    return (NULL);
}
