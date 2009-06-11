#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include "../FileManagement_global.h"

#include <QObject>

#include "../../../IClientPlugin.h"
#include "../../../INetworkPlugin.h"
#include "../IFileManagement.h"
#include "File.h"

/*!
 *  a class used to:
 *  - list directories
 *  - get informations about file(s)
 *  - to open a transfert connexion to the server (just by File::open())
 *  - manage the queue of transfert
 */
//! manage every file transfert and informations
class FILEMANAGEMENTSHARED_EXPORT FileManagement : public IClientPlugin, public INetworkPlugin, public IFileManagement
{
    Q_OBJECT
    Q_INTERFACES(IClientPlugin)
    Q_INTERFACES(INetworkPlugin)
    Q_INTERFACES(IFileManagement)

  // FileManagement can access private methods of File
  // TODO: maybe just set methods as friend instead of the object
  friend class File;

public:
    FileManagement();

    // IClientPlugin
    inline const QByteArray    getName() const { return "FileManagement"; }
    inline const QByteArray    getVersion() const { return "0.1"; }


    // INetworkPlugin
    void recvPacket(const PluginPacket&);


    //IFileManagement
    //! Return a new instance of File. No errors.
    IFile* newFile(quint32 nodeId);
    //! Return an instance of File if the file is found on the server. 0 if not found or permition denied.
    IFile* getFile(quint32 fileId);

    //! Return the full list of readable files. May be incomplete the first time. See SIGNAL(fileListUpdated(quint32)))
    const QHash<quint32,IFile*> getFullFileList() const;
    //! Return the list of readable files of the nodeId. May be incomplete the first time. See SIGNAL(fileListUpdated(quint32)))
    const QList<IFile*> getNodeFileList(quint32 nodeId) const;
    int countNodeFileList(quint32 nodeId) const;
    //TODO: more filters
    //const QList<File*> getFileListByCTime(....); ByMtime By


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
    //! Send the request to update the full file list
    void askForFileFullList() const;
};

#endif // FILEMANAGEMENT_H
