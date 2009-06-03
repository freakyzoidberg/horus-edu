#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>

#include "NetFile.h"

/*!
 *  a class used to:
 *  - list directories
 *  - get informations about file(s)
 *  - to open a transfert connexion to the server (just by NetFile::open())
 *  - manage the queue of transfert
 */
//! manage every file transfert and informations
class FileManager : public QObject
{
  Q_OBJECT

    friend class NetFile;

//private:
//    friend NetFile::NetFile(const CommFileInfo& info);
//    friend NetFile::~NetFile();

public:
    //! return a new instance of NetFile. No errors
    NetFile* newFile(quint32 nodeId);
    //! return an instance of NetFile if the file is found on the server. 0 if not found or permition denied
    NetFile* getFile(quint32 fileId);

private:
    //! contain the list of NetFile
    QHash<quint32,NetFile*> fileList;
    NetFile*                tmpNewFile;

    //! send the request to update the fileInfo of fileId
    void getFileInfo(quint32 fileId);
    //! send the request to open the file fileId and also update the fileInfo
    void getFileConnexion(quint32 fileId, QIODevice::OpenMode mode);

    //! return the list of readable files by the current user
//TODO    const QList<CommFileInfo> getUserFileList();
    //! return the list of readable files of the nodeId
//TODO    const QList<CommFileInfo> getNodeFileList(quint32 nodeId);

public:
    //! called by packetManager when a FILE packet is received
    void receiveFilePacket(QByteArray&);

    //! return the unique instance of FileManager
    static FileManager* globalInstance();
private:
    FileManager();
    static FileManager instance;
};

#endif // FILEMANAGER_H
