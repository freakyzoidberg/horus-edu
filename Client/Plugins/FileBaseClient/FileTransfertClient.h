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

#endif // FILETRANSFERTCLIENT_H
