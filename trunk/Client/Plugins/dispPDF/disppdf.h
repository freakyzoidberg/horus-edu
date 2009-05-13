#ifndef DISPPDF_H
#define DISPPDF_H

#include <QStringList>
#include <QObject>

#include "../../IClientPlugin.h"
#include "../../IPluginNetwork.h"

#include "dispPDFClient.h"
#include "dispPDFNetwork.h"

class DispPDF : public IClientPlugin
{
 Q_OBJECT
 Q_INTERFACES(IClientPlugin)

public:
    DispPDF();
    const QByteArray        getName() const;
    const QByteArray        getVersion() const;
    QStringList             getPluginsConflicts() const;
    QStringList             getPluginsRequired() const;
    QStringList             getPluginsRecommended() const;
    //QStringList           getExports();
    bool                    event(QEvent *);
    bool                    eventHandlerLoad(QEvent *);
    bool                    eventHandlerUnload(QEvent *);

private:
    QByteArray  name;
    QByteArray  version;
    QStringList pluginsConflicts;
    QStringList plugindRequired;
    QStringList pluginsRecommended;

    DispPDFNetwork   *pNetwork;
};

#endif // DISPPDF_H
