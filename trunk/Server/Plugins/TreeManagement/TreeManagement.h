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
    void  gettree(const QVariantHash& request,QVariantHash& response, qint32 iduser); // user or admin protected
    void  setnode(const QVariantHash& request,QVariantHash& response, qint32 iduser); // Admin protected
    void  getnodeinfo(const QVariantHash& request,QVariantHash& response, qint32 iduser); // user or admin protected
    void  getAlltree(const QVariantHash& request,QVariantHash& response, qint32 iduser); //root admin Protected


    int   getidofusernode(const QVariantHash& request, qint32 iduser);
    int   getidofusernodeWoRequest(qint32 iduser);
    void  addnodewithsons(QHash<QString, QVariant > *utree, qint32 id);
    void  addfathers(QHash<QString, QVariant > *utree,const int id);
    bool  delnode(const int id, const int iduser);
    bool  mvnode(const int id, const int newfatherid, const  int iduser);
    bool  addnode(const int fatherid, const QString type, const QString name, const int user_ref, const int iduser);
    bool  editnode(const int nodeid, const QString type, const QString name, const int user_ref, const int iduser);
    QList<QVariant> userlist(const int id_node);
    //! get all node ids for a user
    /*!
      \param id of user
      \return List of nodes id
    */
    QList<int> GetNodeList(int iduser);


    QList<QVariant> getvectorsonsfromidnode(qint32 idnode);

};


#endif // TreeManagement_H
