#ifndef FILETRANSFERTSERVER_H
#define FILETRANSFERTSERVER_H

#include "../../../Common/DataImplementations/FileDataBase/FileTransfert.h"

class UserData;
class FileNetworkPlugin;
class FileTransfertServer : public FileTransfert
{
  Q_OBJECT
public:
	FileTransfertServer(FileData* file, UserData* user, TransfertType type, FileNetworkPlugin* plugin);
	~FileTransfertServer();
	inline UserData*					user() const { return _user; }

private:
	QTimer*								_timer;
	UserData*							_user;
	FileNetworkPlugin*					_networkPlugin;

private slots:
	void								init();
private:
	void								start(QSslSocket* socket);
	void								checkQueue();


	//STATIC: QUEUE MANAGEMENT
public:
	static void							registerSocket(const QByteArray& key, QSslSocket* socket);

private:
	static QList<FileTransfertServer*>	_transferts;
	static QList<FileTransfertServer*>	_queue;
	static QByteArray					generateUniqueKey();
};

#endif // FILETRANSFERTSERVER_H
