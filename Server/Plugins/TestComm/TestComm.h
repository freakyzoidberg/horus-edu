#ifndef TESTCOMM_H
#define TESTCOMM_H

//#include <QObject>
//#include <QStringList>
//#include <QtCore/qplugin.h>
#include <QDebug>

#include "../../IServerPlugin.h"

class TestComm : public IServerPlugin
{
  Q_OBJECT
  Q_INTERFACES(IServerPlugin)

public:
    TestComm();
    ~TestComm();

public:
    const QByteArray  getName() const;
    const QByteArray  getVersion() const;
//const QStringList getPluginsConflicts() const;
//const QStringList getPluginsRequired() const;
//const QStringList getPluginsRecommended() const;
//const QStringList getExports() const;

    void recvPacket(quint32 userId, const ModulePacket&) const;
signals:
    void sendPacket(quint32 userId, const ModulePacket&) const;
};


#endif // TESTCOMM_H
