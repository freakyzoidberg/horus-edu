#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>

#include "NetFile.h"

/*! WARNING, only one file in the same time for the moment!!!!!!!!
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
public:
    //! return the unique instance of FileManager
    static FileManager* globalInstance();

    //! return the info of the fileId
    void getFileInfo(quint32 fileId);
    //! return the QSslSocket of the file of the server and update the fileInfo
    void getFileConnexion(quint32 fileId, QIODevice::OpenMode mode);
    //! return the list of readable files by the current user
//    const QList<CommFileInfo> getUserFileList();
    //! return the list of readable files of the nodeId
//    const QList<CommFileInfo> getNodeFileList(quint32 nodeId);

    //! called by packetManager when a FILE packet is received
    void receiveFilePacket(QByteArray&);

private:
    FileManager();
    bool inUse;
    static FileManager* instance;
//    QObject* callbackObj;
//    const char* callbackFct;
};

#endif // FILEMANAGER_H
