#ifndef FILETRANSFERT_H
#define FILETRANSFERT_H

#include <QObject>
#include <QHash>
#include <QByteArray>
#include <QSslSocket>
#include <QFile>

//! the object for each file transfert
class FileTransfert : public QObject
{
  Q_OBJECT
public:
    FileTransfert(QFile* file);
    const QByteArray& getKey();
    void clientConnected(QSslSocket* socket);

private:
    QByteArray  key;
    //! socket to the client
    QSslSocket* socket;
    //! opened local file
    QFile*      file;

private slots:
    void endOfListening();

private:
    static QHash<QByteArray,FileTransfert*> transferts;
};

#endif // FILETRANSFERT_H
