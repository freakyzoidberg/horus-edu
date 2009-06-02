#include "AdministrationPlugin.h"

Q_EXPORT_PLUGIN2(Administration, Administration)

Administration::Administration()
{
}

bool    Administration::event(QEvent *event)
{
}

const QByteArray   Administration::getName() const
{
    return modName;
}

const QByteArray   Administration::getVersion() const
{
    return modVersion;
}

QStringList   Administration::getPluginsConflicts() const
{
    return modConflicts;
}

QStringList   Administration::getPluginsRequired() const
{
    return modRequired;
}

QStringList   Administration::getPluginsRecommended() const
{
    return modRecommended;
}

QStringList   Administration::getExports() const
{
    return exports;
}
