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

class UserData;
class TreeData;
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
    FileDataBase(quint32 fileId, FileDataBasePlugin* plugin);
    inline ~FileDataBase() {}

public:
    //INTERFACE Data
    void            keyToStream(QDataStream& s);
    void            dataToStream(QDataStream& s);
    void            dataFromStream(QDataStream& s);

    QDebug          operator<<(QDebug debug) const;

    // INTERFACE FileData

#ifdef HORUS_CLIENT
    QVariant        data(int column, int role = Qt::DisplayRole) const;
#endif
#ifdef HORUS_SERVER
    void            fillFromDatabase  (QSqlQuery&);
    void            createIntoDatabase(QSqlQuery&);
    void            saveIntoDatabase  (QSqlQuery&);
    void            deleteFromDatabase(QSqlQuery&);
#endif
};

#endif // FILEDATABASE_H
