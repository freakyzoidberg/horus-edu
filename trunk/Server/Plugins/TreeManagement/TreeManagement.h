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
    void  getnodeinfo(const QVariantHash& request,QVariantHash& response, qint32 iduser);
    void  getAlltree(const QVariantHash& request,QVariantHash& response, qint32 iduser);


    int   getidofusernode(const QVariantHash& request, qint32 iduser);
    void  addnodewithsons(QHash<QString, QVariant > *utree, qint32 id);
    void  addfathers(QHash<QString, QVariant > *utree,const int id);
    void  delnode(const int id);
    QList<QVariant> getvectorsonsfromidnode(qint32 idnode);

};


#endif // TreeManagement_H
