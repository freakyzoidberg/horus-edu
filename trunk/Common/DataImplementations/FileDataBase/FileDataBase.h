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
#include <QSslSocket>
#include "../../Defines.h"
#include "../../FileData.h"
#include "FileDataBasePlugin.h"

class UserData;
class TreeData;
class FileNetworkPlugin;
class FileDataBase : public FileData
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerFileData)
  friend class FileTransfertServer;
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientFileData)
#endif

  friend class FileDataBasePlugin;

public:
    // INTERFACE Data
    void            keyToStream(QDataStream& s);
	void            dataToStream(QDataStream& s) const;
    void            dataFromStream(QDataStream& s);

    QDebug          operator<<(QDebug debug) const;

#ifdef HORUS_CLIENT
    QVariant        data(int column, int role = Qt::DisplayRole) const;
#endif
#ifdef HORUS_SERVER
	quint8     serverRead();
	quint8     serverCreate();
	quint8     serverSave();
	quint8     serverRemove();
#endif


    // INTERFACE FileData
public:
    inline quint32     id() const { return _id; }

    inline QString     name() const { return _name; }
    void               setName(const QString name);

	inline UserData*   owner() const { return _owner; }

	inline TreeData*   node() const { return _node; }
	void               moveTo(TreeData* node);

	inline QString     mimeType() const { return _mimeType; }
	void               setMimeType(const QString name);

    inline QByteArray  hash() const { return _hash; }
	inline quint64	   size() const { return _size; }

    QFile*             file() const;

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
public:
	//! upload the file to the server.
	void                upload();
	//! download the file from the server.
	void                download();
	//! return true if the file is downloaded in local
	bool                isDownloaded() const;

private:
	bool        _isDownloaded;
#endif
};

#endif // FILEDATABASE_H
