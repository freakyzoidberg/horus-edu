#ifndef FILETRANSFERT_H
#define FILETRANSFERT_H

#include <QList>
#include <QByteArray>
#include <QSslSocket>
#include <QTimer>
#include <QFile>
#include <QMutex>
#include <QCryptographicHash>
class FileData;
class FileDataBase;
#define TRANSFERT_BUFFER_SIZE 32768

//! the object for each file transfert
class FileTransfert : public QObject
{
  Q_OBJECT

public:
	enum TransfertType { DOWNLOAD, UPLOAD };
	inline FileData*	file() const { return _fileData; }
	inline const QByteArray& key() const { return _key; }
	//! return the progress value (for a down/up-load)
	inline int			progress() const { return _progress; }

protected:
	FileTransfert(FileData* file, TransfertType type);

	//! the associated FileData*
	FileData*			_fileData;
	//! type : DOWNLOAD / UPLOAD
	TransfertType       _type;
	//! transfert socket
    QSslSocket*         _socket;
	//! local file
    QFile*              _file;
	//! to calculate the hash in live
	QCryptographicHash* _hash;
	//! transfert buffer
	char				_buffer[TRANSFERT_BUFFER_SIZE];
	//! the key to authenticate the new connexion
	QByteArray          _key;
	qint64				_progress;

signals:
	void progressChange(int);
	void finished();

protected slots:
    void socketToFile();
    void fileToSocket(qint64);
};

class FileTransfertList : public QObject, public QList<FileTransfert*>
{
	Q_OBJECT

public:
	inline static FileTransfertList& list() { static FileTransfertList _list; return _list; }
	inline void						append(FileTransfert* t) { QList<FileTransfert*>::append(t); emit started(t); }
	inline void						remove(FileTransfert* t) { QList<FileTransfert*>::removeOne(t); }

signals:
	void							started(FileTransfert*);

private:
									FileTransfertList() {}
									~FileTransfertList() {}
};

#endif // FILETRANSFERT_H
