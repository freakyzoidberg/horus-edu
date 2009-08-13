#ifndef FILE_H
#define FILE_H

#include <QFile>
#include <QMutex>
#include <QSslSocket>

#include "IFile.h"

class FileManagement;

class File : public IFile
{
  Q_OBJECT
  // FileManager can access private methods of FileManager
  //TODO: maybe just set methods as friend instead of the object
  friend class FileManagement;

public:
    //! return the progress value (for a down/up-load)
    int   getProgress() const;
    //! return the informations of the file (size,owner,...)
    const FileInfo& getInfo() const;
    //! return true if the localfile is the same as the server
    bool isSynchronized() const;
    //! open the transfert connexion if needed and the local file
    bool open(OpenMode mode);
    bool isOopen() const;
    //! close after finishing the curent synchronization
    void close();
    //! return the localFileName
    const QString getLocalFileName() const;
    //! set the filename
    void setFileName(const QString&);

protected:
    qint64 writeData(const char* data, qint64 maxSize);
    qint64 readData(char* data, qint64 maxSize);

private:
    //! private constructor, to keep clear of multiple instance of the same file, only File can new
    File(FileManagement* _fileManagement, const FileInfo& info);
    FileManagement* fileManagement;
    //! private destructor, to block delete from outside, only File can delete
    ~File();

    //! called by FileManager, update the File in the list
    void updateFileInfo(const FileInfo& info);
    //! called by FileManager, open the connexion
    void connexionAuthorized(const QByteArray& key);

    //! information of the current file
    FileInfo info;
    //! lock the access of this file if it's in write mode
    //QMutex       lock;

    //! true if the localfile is the same as the server file
    bool synchronized;

    bool connecting;

    //! the socket to the server if needed
    QSslSocket  connexion;
    //! the localfile
    QFile  file;
    //! keep the connexion position
    qint64       connexionPos;

private slots:
    void fileBytesWritten(qint64);
    void connexionReadyRead();
    void connexionBytesWritten(qint64);
    void synchronize();
    void connexionDisconnected();
};

#endif // FILE_H
