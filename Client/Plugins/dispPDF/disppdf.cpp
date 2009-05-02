#include <QtCore/qplugin.h>

#include "disppdf.h"

Q_EXPORT_PLUGIN2(dispPDF, DispPDF)

DispPDF::DispPDF()
{
}

const QByteArray        DispPDF::getName() const
{
    return name;
}

const QByteArray        DispPDF::getVersion() const
{
    return version;
}

QStringList             DispPDF::getPluginsConflicts() const
{
    return pluginsConflicts;
}


QStringList             DispPDF::getPluginsRequired() const
{
    return plugindRequired;
}

//QStringList           getPluginsRecommended() const;
//QStringList           getExports();

bool                    event(QEvent *)
{
    return true;
}
