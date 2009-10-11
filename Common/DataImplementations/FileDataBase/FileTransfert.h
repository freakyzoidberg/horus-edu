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
    ~FileTransfert();

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

protected slots:
    void socketToFile();
    void fileToSocket(qint64);
	void disconnected();
};

class FileTransfertList : public QObject, public QList<FileTransfert*>
{
	Q_OBJECT

public:
	inline static FileTransfertList& list() { static FileTransfertList _list; return _list; }
	inline void						append(FileTransfert* t) { emit started(t);  QList<FileTransfert*>::append(t); }
	inline void						remove(FileTransfert* t) { emit finished(t); QList<FileTransfert*>::removeOne(t); }

	// to be mor clean, implement every used methods to protect changing the qlist from another way
// 	inline int						size() const { return QList<FileTransfert*>::size(); }

signals:
	void							started(FileTransfert*);
	void							finished(FileTransfert*);

private:
									FileTransfertList() {}
									~FileTransfertList() {}
};

#endif // FILETRANSFERT_H
