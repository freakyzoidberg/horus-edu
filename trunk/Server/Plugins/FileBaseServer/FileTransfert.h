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
    FileTransfert(FileData* file);
    ~FileTransfert();
    const QByteArray& key() const;
    void clientConnected(QSslSocket* socket);

private:
    QByteArray  _key;
    //! socket to the client
    QSslSocket* _socket;
    //! opened local file
    QFile*      _file;

    QTimer*     _timer;

signals:
    void start();

private slots:
    void startSlot();
    void socketToFile();
    void fileToSocket(qint64);

public:
    static void registerSocket(const QByteArray& key, QSslSocket* socket);
private:
    static QHash<QByteArray,FileTransfert*> _transferts;
};

#endif // FILETRANSFERT_H
