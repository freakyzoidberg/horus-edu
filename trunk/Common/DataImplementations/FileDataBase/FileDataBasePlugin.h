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

  friend class FileDataBase;

// Plugin Interface
public:
	inline const QString	pluginName() const { return "File Data Base"; }
	inline const QString	pluginVersion() const { return "0.1"; }
	void					load();


// DataPlugin Interface
public:
	QList<Data*>			allDatas() const;
#ifdef HORUS_CLIENT
	void					dataHaveNewKey(Data*d, QDataStream& s);
#endif
#ifdef HORUS_SERVER
	void					loadData();
	QList<Data*>			datasForUpdate(UserData* user, QDateTime date);
#endif
protected:
    //! Return the pointer to the Data with a his unique key read in the stream
	Data*					dataWithKey(QDataStream& s);


// FileDataPlugin Interface
public:
	FileData*								file(quint32 fileId);
	QList<FileData*>						filesInNode(quint32 nodeId) const;
	QList<FileData*>						filesInNode(const TreeData *node) const;
	QList<FileData*>						filesInNodeAndUser(quint32 nodeId, quint32 userId) const;
	QList<FileData*>						filesInNodeAndUser(const TreeData *node, const UserData* user) const;
	inline const QHash<quint32,FileData*>&	allFiles() const { return _files; }
	FileData*								createFile(TreeData*);

private:
	QHash<quint32,FileData*>	_files;
#ifdef HORUS_SERVER
	FileServer*					_server;
#endif
};

#endif // FILEDATABASEPLUGIN_H
