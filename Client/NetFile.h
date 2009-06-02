#ifndef NETFILE_H
#define NETFILE_H

#include <QFile>
#include <QMutex>
#include <QSslSocket>

#include "../Common/CommFileInfo.h"

class NetFile : public QIODevice
{
  Q_OBJECT
public:
    //! return a new instance of NetFile. No errors
    static NetFile* newFile(quint32 nodeId);
    //! return an instance of NetFile if the file is found on the server. 0 if not found or permition denied
    static NetFile* getFile(quint32 fileId);

private:
    //! contain the list of NetFile
    static QHash<quint32,NetFile*> fileList;

    //! private constructor, to keep clear of multiple instance of the same file
    NetFile(const CommFileInfo& info);
    //! private destructor, to block delete from outside
    ~NetFile();

signals:
    //! emitted when the fileInformation change
    void fileInfoUpdated();
    //! emitted when a connexion to the server is opened (maybe useless)
    void connexionOpened();
    //! emitted when the progress value change (for a down/upload)
    void transfertProgress(int percent);

public:
    //! return the progress value (for a down/upload)
    int   getProgress();

    //! return the informations of the file (size,owner,...)
    const CommFileInfo& getInfo();



/******** virtual in QIODevice *********/
    //bool atEnd () const;
    //qint64 bytesAvailable () const;
    //qint64 bytesToWrite () const;
    //bool canReadLine () const;
    //! finish to sync, close the connexion and the local file and update the server informations onto the server
    void close ();
    //bool isSequential () const;
    //! open the transfert connexion if needed and the local file
    bool open(OpenMode mode);
    qint64 pos() const;
    //QByteArray readLine(qint64 maxSize=0);
    //qint64 size () const;
    //bool waitForBytesWritten(int timeout=-1);
    //bool waitForReadyRead(int timeout=-1);
protected:
    //! read from localfile if present, or read from the socket and write to the localfile
    qint64 readData(char* data, qint64 maxSize);
    //qint64 readLineData(char* data, qint64 maxSize);
    //! write to the localfile and to the socket
    qint64 writeData(const char* data, qint64 maxSize);
/****************************************/




///////////////// INTERNAL USE ONLY (including FileManager)

public:
    //! called by FileManager, update the NetFile in the list
    void updateFileInfo(const CommFileInfo& info);
    //! called by FileManager, open the connexion
    void connexionAuthorized(const QByteArray& key);

private slots:
    void connexionReadyRead();
    void connexionBytesWritten(qint64);

private:
    //! information of the current file
    CommFileInfo info;
    //! lock the access of this file if it's in write mode
    QMutex       lock;
    //! the local file
    QFile        localFile;
    //! keep the localFile position to be able to lseek when data are received from the server
    qint64       localFilePos;
    //! the socket to the server if needed
    QSslSocket*  connexion;
    //! keep the connexion position
    qint64       connexionPos;
};

#endif // NETFILE_H
