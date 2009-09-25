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

// Plugin Interface
public:
    inline const QString pluginName() const { return "File Data Base"; }
    inline const QString pluginVersion() const { return "0.1"; }
    void                 load();


// DataPlugin Interface
public:
    Data*           getNewData();
#ifdef HORUS_CLIENT
    void            dataHaveNewKey(Data*d, QDataStream& s);
#endif
#ifdef HORUS_SERVER
    void            loadDataBase(QSqlQuery&);
    void            sendUpdates(QSqlQuery&, UserData* user, QDateTime date);
#endif
protected:
    //! Return the pointer to the Data with a his unique key read in the stream
    Data*                getDataWithKey(QDataStream& s);


// FileDataPlugin Interface
public:
    FileData*            getFile(quint32 fileId);
	QHash<quint32, FileData*> getFilesPerNode(quint32 nodeId);
	QHash<quint32, FileData*> getFilesPerNode(const TreeData *node);
	QHash<quint32, FileData*> getFilesPerNodeAndUser(quint32 nodeId, quint32 userId);
	QHash<quint32, FileData*> getFilesPerNodeAndUser(const TreeData *node, const UserData* user);


private:
    QHash<quint32,FileData*> files;
#ifdef HORUS_SERVER
    FileServer*          server;
#endif
};

#endif // FILEDATABASEPLUGIN_H
