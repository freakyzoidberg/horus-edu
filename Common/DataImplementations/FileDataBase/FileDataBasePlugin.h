#ifndef FILEDATABASEPLUGIN_H
#define FILEDATABASEPLUGIN_H


#include <QHash>
#include "../../FileDataPlugin.h"

class Data;
class FileData;
class FileDataBase;
class FileServer;
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

    FileData*       getFile(quint32 fileId);
    FileData*       getFile(quint32 nodeId, QString fileName);

    void            load();

#ifdef HORUS_CLIENT
    void            dataHaveNewKey(Data*d, QDataStream& s);
#endif
#ifdef HORUS_SERVER
    void            loadDataBase(QSqlQuery&);
#endif

protected:
    //! Return the pointer to the Data with a his unique key read in the stream
    Data*                getDataWithKey(QDataStream& s);

private:
    QHash<quint32,FileData*> files;
#ifdef HORUS_SERVER
    FileServer*          server;
#endif
};

#endif // FILEDATABASEPLUGIN_H