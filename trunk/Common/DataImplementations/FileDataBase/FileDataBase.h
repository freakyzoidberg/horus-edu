#ifndef FILEDATABASE_H
#define FILEDATABASE_H

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
#include "FileBase.h"

class UserData;
class TreeData;
class QSslSocket;
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

public:
    // INTERFACE Data
    void            keyToStream(QDataStream& s);
    void            dataToStream(QDataStream& s);
    void            dataFromStream(QDataStream& s);

    QDebug          operator<<(QDebug debug) const;

#ifdef HORUS_CLIENT
    QVariant        data(int column, int role = Qt::DisplayRole) const;
#endif
#ifdef HORUS_SERVER
    void            fillFromDatabase  (QSqlQuery&);
    void            createIntoDatabase(QSqlQuery&);
    void            saveIntoDatabase  (QSqlQuery&);
    void            deleteFromDatabase(QSqlQuery&);
#endif


    // INTERFACE FileData
public:
    inline quint32     id() const { return _id; }

    inline QString     name() const { return _name; }
    void               setName(const QString name);

    inline QString     mimeType() const { return _mimeType; }

    inline TreeData*   node() const { return _node; }
    void               moveTo(TreeData* node);

    inline UserData*   owner() const { return _owner; }

    inline QByteArray  hash() const { return _hash; }

#ifdef HORUS_CLIENT
    File*              device() const { return _device; }
#endif
#ifdef HORUS_SERVER
    QFile*             device() const { return _device; }
#endif

private:
    FileDataBase(quint32 fileId, FileDataBasePlugin* plugin);
    quint32    _id;
    QString    _name;
    QString    _mimeType;
    quint64    _size;
    TreeData*  _node;
    UserData*  _owner;
    QByteArray _hash;
#ifdef HORUS_CLIENT
    FileBase*  _device;
#endif
#ifdef HORUS_SERVER
    QFile*     _device;
#endif
};

#endif // FILEDATABASE_H
