#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>

#include "IFileManager.h"
#include "File.h"

/*!
 *  a class used to:
 *  - list directories
 *  - get informations about file(s)
 *  - to open a transfert connexion to the server (just by File::open())
 *  - manage the queue of transfert
 */
//! manage every file transfert and informations
class FileManager : public IFileManager
{
  Q_OBJECT

  // FileManager can access private methods of FileManager
  // TODO: maybe just set methods as friend instead of the object
  friend class File;

public:
    //! Return a new instance of File. No errors.
    IFile* newFile(quint32 nodeId);
    //! Return an instance of File if the file is found on the server. 0 if not found or permition denied.
    IFile* getFile(quint32 fileId);

    //! Return the full list of readable files. May be incomplete the first time. See SIGNAL(fileListUpdated(quint32)))
    //const QList<IFile*> getFullFileList() const;
    const QHash<quint32,IFile*> getFullFileList() const;
    //! Return the list of readable files of the nodeId. May be incomplete the first time. See SIGNAL(fileListUpdated(quint32)))
    const QList<IFile*> getNodeFileList(quint32 nodeId) const;
    //TODO: more filters
    //const QList<File*> getFileListByCTime(....); ByMtime By

//signals:
//    //! Signal emmited when a node is updated.(file creation / file deleted / list just loaded)
//    void nodeFileListUpdated(quint32 nodeId);
//    //! Signal emmited when the fileHash is updated.(file creation / file deleted / list just loaded)
//    void fileListUpdated();

private:
    //! Contain all the list of File,
    QHash<quint32,IFile*> fileHash;
    //! Contain the new file created, before receiving the new fileInfo about it.
    File*                tmpNewFile;
    bool                 haveFullList;

    //! Send the request to update the fileInfo of fileId.
    void askForFileInfo(quint32 fileId) const;
    //! Send the request to open the file fileId and also update the fileInfo.
    void askForFileConnexion(quint32 fileId, QIODevice::OpenMode mode) const;

    void askForFileFullList() const;


public slots:
    //! Called by packetManager when a FILE packet is received.
    void receiveFilePacket(QByteArray);



    //! Return the unique instance of FileManager.
    static FileManager* instance();
private:
    FileManager();
};

#endif // FILEMANAGER_H
