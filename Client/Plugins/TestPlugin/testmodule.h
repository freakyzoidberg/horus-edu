#ifndef TESTMODULE_H
#define TESTMODULE_H

#include <QObject>
#include <QEvent>
#include <QStringList>

#include "../../IClientPlugin.h"
#include "../../IPluginNetwork.h"
#include "../../LoadPluginEvent.h"
#include "PluginNetwork.h"

class testPlugin : public IClientPlugin//,  public IPluginNetwork
{
 Q_OBJECT
 Q_INTERFACES(IClientPlugin)// IPluginNetwork)

public:
    testPlugin();
    ~testPlugin();

public:
     void setModName(const QByteArray);
     void setModVersion(const QByteArray);
     void setModConflicts(const QString);
     void setModRequired(const QString);
     void setModRecommended(const QString);
     void setExports(const QString);

  public:
     const QByteArray        getName() const;
     const QByteArray        getVersion() const;
     QStringList    getPluginsConflicts() const;
     QStringList    getPluginsRequired() const;
     QStringList    getPluginsRecommended() const;
     QStringList    getExports() const;

    bool    event(QEvent *);
    bool    eventHandlerLoad(QEvent *);
    bool    eventHandlerUnload(QEvent *);

 private:
    QByteArray         modName;
    QByteArray         modVersion;
    QStringList     modConflicts;
    QStringList     modRequired;
    QStringList     modRecommended;
    QStringList     exports;

    PluginNetwork   *pNetwork;;
};


#endif // TESTMODULE_H
