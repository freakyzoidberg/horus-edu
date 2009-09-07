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
  Q_INTERFACES(TreeData)

  friend class TreeDataBasePlugin;
private:
    TreeDataBase(quint32 nodeId, TreeDataBasePlugin* plugin);
    inline ~TreeDataBase() {}

    quint32     _id;
    UserData*   _user;
    QString     _name;
    QString     _type;


public:
    //INTERFACE Data
    void            keyToStream(QDataStream& s);
    void            dataToStream(QDataStream& s);
    void            dataFromStream(QDataStream& s);

    QDebug          operator<<(QDebug debug) const;

    // INTERFACE TreeData
    inline int     id() const { return _id; }

    TreeData*           createChild(const QString name, const QString type, UserData* user);
    void                remove();
    void                moveTo(TreeData* father);

    inline const QString name() const { return objectName(); }
    void                setName(const QString name);

    inline UserData*    user() const { return _user; }
    void                setUser(UserData* user);

    inline const QString type() const { return _type; }
    void                setType(const QString type);

    bool                isDescendantOf(TreeData* parent);

#ifdef HORUS_CLIENT
    QVariant        data(int column, int role = Qt::DisplayRole) const;
#endif
#ifdef HORUS_SERVER
    void            fillFromDatabase  (QSqlQuery&);
    void            createIntoDatabase(QSqlQuery&);
    void            saveIntoDatabase  (QSqlQuery&);
    void            deleteFromDatabase(QSqlQuery&);
    QByteArray      newSession(QSqlQuery&, const QDateTime& end);
    void            destroySession(QSqlQuery&);
#endif
};

#endif // TREEDATABASE_H
