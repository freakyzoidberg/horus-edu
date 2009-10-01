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
	FileData*           getFile(quint32 fileId);
	QList<FileData*>	getFilesInNode(quint32 nodeId) const;
	QList<FileData*>	getFilesInNode(const TreeData *node) const;
	QList<FileData*>	getFilesInNodeAndUser(quint32 nodeId, quint32 userId) const;
	QList<FileData*>	getFilesInNodeAndUser(const TreeData *node, const UserData* user) const;
	FileData*			createNewFile(TreeData*);

private:
    QHash<quint32,FileData*> files;
#ifdef HORUS_SERVER
    FileServer*          server;
#endif
};

#endif // FILEDATABASEPLUGIN_H
