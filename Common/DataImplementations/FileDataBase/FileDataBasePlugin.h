#ifndef FILEDATABASEPLUGIN_H
#define FILEDATABASEPLUGIN_H

#include <QHash>
#include "../../FileDataPlugin.h"

class Data;
class FileData;
class FileDataBase;
class FileDataBasePlugin : public FileDataPlugin
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerFileDataPlugin)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientFileDataPlugin)
#endif

public:
    inline FileDataBasePlugin() {}
    inline const QString pluginName() const { return "File Data Base"; }
    inline const QString pluginVersion() const { return "0.1"; }

    FileData*    getFile(quint32 fileId);
    FileData*    getFile(quint32 nodeId, QString fileName);

#ifdef HORUS_CLIENT
    void                 dataHaveNewKey(Data*d, QDataStream& s);
#endif
#ifdef HORUS_SERVER
    bool                 verifyDataBase(QSqlQuery&);
    void                 userDisconnected(FileData* user);
    FileData*            authenticatePassword(QSqlQuery& query, const QString& login, const QByteArray& password);
    FileData*            authenticateSession (QSqlQuery& query, const QString& login, const QByteArray& sesion);
#endif

protected:
    //! Return the pointer to the Data with a his unique key read in the stream
    Data*                getDataWithKey(QDataStream& s);

private:
    QHash<quint32,FileData*> nodes;
};

#endif // FILEDATABASEPLUGIN_H