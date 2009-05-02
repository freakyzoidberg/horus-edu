#ifndef DISPPDF_H
#define DISPPDF_H

#include <QStringList>
#include <QObject>

#include "../../IClientPlugin.h"
#include "../../IPluginNetwork.h"
#include "dispPDFClient.h"


class DispPDF : public QObject, public IClientPlugin
{
 Q_OBJECT
 Q_INTERFACES(IClientPlugin)

public:
    DispPDF();
//    Iclient                 *client;
    const QByteArray        getName() const;
    const QByteArray        getVersion() const;
    QStringList             getPluginsConflicts() const;
    QStringList             getPluginsRequired() const;
    //QStringList           getPluginsRecommended() const;
    //QStringList           getExports();
    bool                    event(QEvent *);

private:
    QByteArray  name;
    QByteArray  version;
    QStringList pluginsConflicts;
    QStringList plugindRequired;
};

#endif // DISPPDF_H
