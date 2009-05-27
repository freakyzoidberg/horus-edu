#ifndef TREEMANAGEMENT_H
#define TREEMANAGEMENT_H

#include <QDebug>

#include "../IServer.h"
#include "../IServerPlugin.h"

//! a Server Plugin to allow management of organisation tree
class TreeManagement : public IServerPlugin
{
  Q_OBJECT
  Q_INTERFACES(IServerPlugin)
    typedef void (TreeManagement::*requestFunction)(const QVariantHash& request,QVariantHash& response, qint32 iduser);
public:
    TreeManagement();
    ~TreeManagement();

public:
    inline const QByteArray  name()    const { return "TreeManagement"; }
    inline quint8            version() const { return 1; }

    void recvPacket(quint32 userId, const PluginPacket&);

private:
     QHash<QByteArray,requestFunction> requestFunctions;

    void  unknownRequest(const QVariantHash& request,QVariantHash& response, qint32 iduser);
    void  gettree(const QVariantHash& request,QVariantHash& response, qint32 iduser);
    void  setnode(const QVariantHash& request,QVariantHash& response, qint32 iduser);

    int   getidofusernode(const QVariantHash& request, qint32 iduser);

};


#endif // TreeManagement_H
