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
    inline TreeDataBase(quint32 nodeId, TreeDataBasePlugin* plugin) : TreeData(nodeId, (TreeDataPlugin*)plugin) { }
    inline ~TreeDataBase() {}

    quint32 userId;
    QString name;
    QString type;


    // INTERFACE TreeData
public:
    void            createChild(int userId, QString name, QString type);
    void            remove();
    void            moveTo(int idfather);
    void            moveTo(TreeData* father);
    inline QString  getName() const { return objectName(); }
    void            setName(QString name);
    inline int      getUserId() const { return userId; }
    void            setUserId(int user);
    inline QString  getType() const { return type; }
    void            setType(QString type);
    bool            isDescendantOf(int parent);
    bool            isDescendantOf(TreeData* parent);
    bool            canChange();

    //INTERFACE Data
public:
    void            keyToStream(QDataStream& s);
    void            dataToStream(QDataStream& s);
    void            dataFromStream(QDataStream& s);

    QDebug          operator<<(QDebug debug) const;
#ifdef HORUS_CLIENT
    QVariant        data(int column, int role = Qt::DisplayRole) const;
    static QMap<QString,QIcon> icons;
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
