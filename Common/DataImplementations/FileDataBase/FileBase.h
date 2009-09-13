#ifndef FILEBASE_H
#define FILEBASE_H

#include <QFile>
#include <QSslSocket>

#include "../../../Common/File.h"

class FileDataBase;
class FileNetworkPlugin;
class FileBase : public File
{
  Q_OBJECT

  friend class FileBasePlugin;
  friend class FileDataBase;

public:
    //! return the progress value (for a down/up-load)
    int   progress() const;
    //! open the transfert connexion if needed and the local file
    bool  open(OpenMode mode);
    //! true if the device is open
    bool  isOopen() const;
    //! close after finishing the curent synchronization
    void  close();

    //! download the file from the server.
    void  download();
    //! upload the file to the server.
    void  upload();

    //! called by FileNetworkPlugin after receiving the download authorisation
    void        download(const QByteArray& key);
    //! called by FileNetworkPlugin after receiving the upload authorisation
    void        upload(const QByteArray& key);

protected:
    qint64 writeData(const char* data, qint64 maxSize);
    qint64 readData(char* data, qint64 maxSize);

private:
    //! private constructor, to keep clear of multiple instance of the same file, only File can new
    FileBase(FileDataBase* fileData, FileNetworkPlugin* netPlugin);
    //! private destructor, to block delete from outside, only File can delete
    ~FileBase();

    //! the socket to the server if needed
    QSslSocket  _socket;
    //! the localfile
    QFile       _file;

    FileNetworkPlugin* _netPlugin;

    void connectToServer(const QByteArray& key);

private slots:
    void connexionReadyRead();
    void connexionBytesWritten(qint64);
    void connexionDisconnected();
};

#endif // FILEBASE_H
