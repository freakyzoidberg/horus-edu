#ifndef FILETRANSFERTCLIENT_H
#define FILETRANSFERTCLIENT_H

#include "../../../Common/DataImplementations/FileDataBase/FileTransfert.h"

class FileTransfertClient : public FileTransfert
{
  Q_OBJECT
public:
	FileTransfertClient(FileData* file, TransfertType type, const QByteArray& key);
	inline int			speed() const { return _speed; }
	inline int			isFinished() const { return _isFinished; }


private:
	void				connectToServer();

	bool				_isFinished;
	int					_speed;
	QTimer				_speedTimer;
	qint64				_lastProgress;
	uint				_startTime;

signals:
	void				speedChange(int);

private slots:
	void				connexionEncrypted();
	void				calcSpeed();
	void				finish();
};

class FileTransfertQueue : public QObject
{
	Q_OBJECT

public:
	static FileTransfertQueue*		instance() { static FileTransfertQueue* queue = new FileTransfertQueue;	return queue; }
	inline static const QList<FileTransfertClient*> list() { return instance()->_list; }
	
	inline void						append(FileTransfertClient* t) { _list.append(t); emit started(t); }
	inline void						remove(FileTransfertClient* t) { _list.removeOne(t); }

signals:
	void							started(FileTransfert*);

private:
									FileTransfertQueue() {}
									~FileTransfertQueue() {}
	QList<FileTransfertClient*>		_list;
};

#endif // FILETRANSFERTCLIENT_H
