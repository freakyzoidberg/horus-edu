#ifndef FileDATABASE_H
#define FileDATABASE_H

#ifdef HORUS_SERVER
    #include <QtSql>
#endif
#ifdef HORUS_CLIENT
    #include <QVariant>
#endif
#include <QByteArray>
#include <QDateTime>
#include "../../Defines.h"
#include "../../FileData.h"
#include "FileDataBasePlugin.h"

class FileDataBase : public FileData
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerFileData)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientFileData)
#endif

  friend class FileDataBasePlugin;
private:
    FileDataBase(quint32 nodeId, FileDataBasePlugin* plugin);
    inline ~FileDataBase() {}

    quint32 userId;
    QString name;
    QString type;


public:
    //INTERFACE Data
    void            keyToStream(QDataStream& s);
    void            dataToStream(QDataStream& s);
    void            dataFromStream(QDataStream& s);

    QDebug          operator<<(QDebug debug) const;

    // INTERFACE FileData
    void            createChild(int userId, QString name, QString type);
    void            remove();
    void            moveTo(int idfather);
    void            moveTo(FileData* father);
    inline QString  getName() const { return objectName(); }
    void            setName(QString name);
    inline int      getUserId() const { return userId; }
    void            setUserId(int user);
    inline QString  getType() const { return type; }
    void            setType(QString type);
    bool            isDescendantOf(int parent);
    bool            isDescendantOf(FileData* parent);
    bool            canChange();

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

#endif // FileDATABASE_H
