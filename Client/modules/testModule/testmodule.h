#ifndef TESTMODULE_H
#define TESTMODULE_H

#include <QObject>
#include <QEvent>
#include <QStringList>

#include "../../IClientPlugin.h"
#include "PluginNetwork.h"

class TestModule : public QObject, public IClientPlugin
{
 Q_OBJECT
 Q_INTERFACES(IClientPlugin)

public:
    TestModule();

public:
    void setModName(const QString);
     void setModVersion(const QString);
     void setModConflicts(const QString, const QString);
     void setModRequired(const QString, const QString);
     void setModRecommended(const QString, const QString);
     void setExports(const QStringList);

  public:
     QString    getName() const;
     QString    getVersion() const;
     QStringList   getPluginsConflicts() const;
     QStringList   getPluginsRequired() const;
     QStringList   getPluginsRecommended() const;
     QStringList  getExports() const;

    bool    event(QEvent *);
    bool    eventHandlerLoad();
    bool    eventHandlerUnload();

 private:
    QString         modName;
    QString         modVersion;
    QStringList     modConflicts;
    QStringList     modRequired;
    QStringList     modRecommended;
    QStringList     exports;
    PluginNetwork   pNetwork;;
};

#endif // TESTMODULE_H
