#ifndef FILEBASE_H
#define FILEBASE_H

#include <QFile>
#include <QSslSocket>

#include "../../../Common/File.h"

class FileDataBase;
class FileDataBasePlugin;
class FileBase : public File
{
  Q_OBJECT

  friend class FileBasePlugin;

public:
    //! return the progress value (for a down/up-load)
    int   getProgress() const;
    //! return true if the localfile is the same as the server
    bool isSynchronized() const;
    //! open the transfert connexion if needed and the local file
    bool open(OpenMode mode);
    bool isOopen() const;
    //! close after finishing the curent synchronization
    void close();

protected:
    qint64 writeData(const char* data, qint64 maxSize);
    qint64 readData(char* data, qint64 maxSize);

private:
    //! private constructor, to keep clear of multiple instance of the same file, only File can new
    FileBase(FileDataBasePlugin* plugin, FileDataBase* fileData);
    //! private destructor, to block delete from outside, only File can delete
    ~FileBase();

    //! called by FileManager, open the connexion
    void connexionAuthorized(const QByteArray& key);

    //! true if the localfile is the same as the server file
    bool synchronized;

    bool connecting;

    //! the socket to the server if needed
    QSslSocket  connexion;
    //! the localfile
    QFile  file;
    //! keep the connexion position
    qint64       connexionPos;

    FileDataBase* fileData;

    FileDataBasePlugin* filePlugin;

private slots:
    void fileBytesWritten(qint64);
    void connexionReadyRead();
    void connexionBytesWritten(qint64);
    void synchronize();
    void connexionDisconnected();
};

#endif // FILEBASE_H
