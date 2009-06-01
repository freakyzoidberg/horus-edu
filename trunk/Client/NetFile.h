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
    static NetFile* newFile(quint32 nodeId);
    static NetFile* getFile(quint32 fileId);

private:
    //! private constructor, to keep clear of multiple instance of the same file
    NetFile(quint32);
    //! private destructor, to block delete from outside
    ~NetFile();

public:
    bool  isInfoAvailable();
    bool  isSynchronized();
    int   getProgress();

    const CommFileInfo& getInfo();

    bool waitForInfoAvailable(int timeout=-1);
    bool waitForSynchronized(int timeout=-1);

    /******** virtual in QIODevice *********/
    //bool atEnd () const;
    //qint64 bytesAvailable () const;
    //qint64 bytesToWrite () const;
    //bool canReadLine () const;
    //void close ();
    //bool isSequential () const;
    //bool open(OpenMode mode);
    //qint64 pos() const;
    //QByteArray readLine(qint64 maxSize=0);
    //qint64 size () const;
    //bool waitForBytesWritten(int timeout=-1);
    //bool waitForReadyRead(int timeout=-1);
protected:
    qint64 readData(char* data, qint64 maxSize);
    //qint64 readLineData(char* data, qint64 maxSize);
    qint64 writeData(const char* data, qint64 maxSize);
/****************************************/

private:
    CommFileInfo info;
    QMutex       infoLock;
    QMutex       syncLock;
    QFile        localFile;
    QSslSocket   serverFile;

    static QHash<quint32,NetFile*> fileList;

signals:
    void infoAvailable();
    void progress(int percent);
    void synchronized();
};

#endif // NETFILE_H
