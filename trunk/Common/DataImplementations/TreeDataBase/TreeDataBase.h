#ifndef TREEDATABASE_H
#define TREEDATABASE_H

#ifdef HORUS_SERVER
    #include <QtSql>
#endif
#ifdef HORUS_CLIENT
    #include <QVariant>
#endif
#include <QByteArray>
#include <QDateTime>
#include "../../Defines.h"
#include "../../TreeData.h"
#include "TreeDataBasePlugin.h"

class TreeDataBase : public TreeData
{
  Q_OBJECT
#ifdef HORUS_SERVER
    Q_INTERFACES(ServerTreeData)
#endif
#ifdef HORUS_CLIENT
    Q_INTERFACES(ClientTreeData)
#endif

    friend class TreeDataBasePlugin;
 private:
  TreeDataBase(quint32 nodeId, TreeDataBasePlugin* plugin);
  inline ~TreeDataBase() {}

  quint32     _id;
  UserData*   _user;
  QString     _name;
  QString     _type;
  QList<TreeData*> _children;
  TreeDataBase*	_parent;

 public:
  //INTERFACE Data
  void            keyToStream(QDataStream& s);
  void            dataToStream(QDataStream& s) const;
  void            dataFromStream(QDataStream& s);

  QDebug          operator<<(QDebug debug) const;

  // INTERFACE TreeData
  inline quint32      id() const { return _id; }

  TreeData*           createChild(const QString name, const QString type, UserData* user);
  void                recursRemove();
  void                moveTo(TreeData* father);

  inline const QString name() const { return objectName(); }
  void                setName(const QString name);

  inline UserData*    user() const { return _user; }
  void                setUser(UserData* user);

  inline const QString type() const { return _type; }
  void                setType(const QString type);

  inline TreeData*	parent() const { return _parent; }
  void				setParent(TreeData*);
  inline const QList<TreeData*>&	children() const { return _children; }

  bool                isDescendantOf(TreeData* parent);

#ifdef HORUS_CLIENT
  QVariant        data(int column, int role = Qt::DisplayRole) const;
#endif
#ifdef HORUS_SERVER
  quint8			serverRead();
  quint8			serverCreate();
  quint8			serverSave();
  quint8			serverRemove();
  QByteArray		newSession(const QDateTime& end);
  void            destroySession();
#endif

private slots:
	void userRemoved();
};

#endif // TREEDATABASE_H
