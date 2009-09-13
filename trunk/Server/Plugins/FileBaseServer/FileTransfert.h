#ifndef FILETRANSFERT_H
#define FILETRANSFERT_H

#include <QHash>
#include <QByteArray>
#include <QSslSocket>
#include <QTimer>
#include <QFile>
class FileData;

//! the object for each file transfert
class FileTransfert : public QObject
{
  Q_OBJECT
public:
    enum TransfertType { DOWNLOAD, UPLOAD };
    FileTransfert(FileData* file, TransfertType type);
    ~FileTransfert();
    const QByteArray& key() const;
    void clientConnected(QSslSocket* socket);

private:
    QByteArray  _key;
    //! socket to the client
    QSslSocket* _socket;
    //! opened local file
    QFile*      _file;

    FileData*   _fileData;

    QTimer*     _timer;
    TransfertType _type;

private slots:
    void init();
    void socketToFile();
    void fileToSocket(qint64);

public:
    static void registerSocket(const QByteArray& key, QSslSocket* socket);
private:
    static QHash<QByteArray,FileTransfert*> _transferts;
};

#endif // FILETRANSFERT_H
