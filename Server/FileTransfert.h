#ifndef FILETRANSFERT_H
#define FILETRANSFERT_H

#include <QHash>
#include <QByteArray>
#include <QSslSocket>
#include <QTimer>
#include <QFile>

//! the object for each file transfert
class FileTransfert : public QObject
{
  Q_OBJECT
public:
    FileTransfert(QFile* file);
    ~FileTransfert();
    const QByteArray& getKey() const;
    void clientConnected(QSslSocket* socket);

private:
    QByteArray  key;
    //! socket to the client
    QSslSocket* socket;
    //! opened local file
    QFile*      file;

    QTimer*     timer;

signals:
    void start();

private slots:
    void startSlot();
    void read();
    void write();

private:
    static QHash<QByteArray,FileTransfert*> transferts;
};

#endif // FILETRANSFERT_H
