#ifndef NETFILE_H
#define NETFILE_H

#include <QFile>
#include <QMutex>
#include <QSslSocket>

#include "../Common/CommFileInfo.h"

class FileManager;
class NetFile : public QFile
{
  Q_OBJECT

public:
    //! return the progress value (for a down/up-load)
    int   getProgress() const;
    //! return the informations of the file (size,owner,...)
    const CommFileInfo& getInfo() const;
    //! return true if the localfile is the same as the server
    bool isSynchronized() const;



/*** overloads from QFile ***/
public:
    //! open the transfert connexion if needed and the local file
    bool open(OpenMode mode);
    //! finish to sync, close the connexion and the local file and update the server informations onto the server
    void close ();
protected:
    //! write to the localfile and to the socket
    qint64 writeData(const char* data, qint64 maxSize);
/****************************/

signals:
    //! emitted an error append
    void error(int code, QString message);
    //! emitted when the fileInformation change
    void fileInfoUpdated();
    //! emitted when the localfile is the same as the server
    void fileSynchronized();
    //! emitted when a connexion to the server is opened (maybe useless)
    void connexionOpened();
    //! emitted when the progress value change (for a down/upload)
    void transfertProgress(int percent);

// FileManager can access private methods/props
friend class FileManager;

private:
    //! private constructor, to keep clear of multiple instance of the same file, only NetFile can new
    NetFile(const CommFileInfo& info);
    //! private destructor, to block delete from outside, only NetFile can delete
    ~NetFile();

private slots:
    void connexionReadyRead();
    void connexionBytesWritten(qint64);

private:
    //! called by FileManager, update the NetFile in the list
    void updateFileInfo(const CommFileInfo& info);
    //! called by FileManager, open the connexion
    void connexionAuthorized(const QByteArray& key);

    //! information of the current file
    CommFileInfo info;
    //! lock the access of this file if it's in write mode
    //QMutex       lock;

    //! true if the localfile is the same as the server file
    bool synchronized;

    //! the socket to the server if needed
    QSslSocket*  connexion;
    //! keep the connexion position
    qint64       connexionPos;
};

#endif // NETFILE_H
