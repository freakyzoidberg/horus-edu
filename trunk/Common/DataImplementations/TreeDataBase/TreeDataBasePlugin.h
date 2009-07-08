#ifndef TREEDATABASEPLUGIN_H
#define TREEDATABASEPLUGIN_H

#include <QHash>
#include "../../TreeDataPlugin.h"

class Data;
class TreeData;
class TreeDataBase;
class TreeDataBasePlugin : public TreeDataPlugin
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerTreeDataPlugin)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientTreeDataPlugin)
#endif

public:
    TreeDataBasePlugin();
    inline const QString pluginName() const { return "Tree Data Base"; }
    inline const QString pluginVersion() const { return "0.1"; }
    inline const QString getDataType() const { return "Tree"; }
    TreeData*            getNode(quint32 nodeId);

#ifdef HORUS_CLIENT
    void                 dataHaveNewKey(Data*d, QDataStream& s);
    QAbstractItemModel*  getTreeModel();
#endif
#ifdef HORUS_SERVER
    bool                 verifyDataBase(QSqlQuery&);
    void                 userDisconnected(TreeData* user);
    TreeData*            authenticatePassword(QSqlQuery& query, const QString& login, const QByteArray& password);
    TreeData*            authenticateSession (QSqlQuery& query, const QString& login, const QByteArray& sesion);
#endif

protected:
    //! Return the pointer to the Data with a his unique key read in the stream
    Data*                getDataWithKey(QDataStream& s);

private:
    QHash<quint32,TreeData*> nodes;
};

#endif // TREEDATABASEPLUGIN_H
