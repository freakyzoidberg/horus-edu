#ifndef IFILEPLUGIN_H
#define IFILEPLUGIN_H

#include <QHash>

class IFile;

/*!
 *  a class used to:
 *  - list directories
 *  - get informations about file(s)
 *  - to open a transfert connexion to the server (just by File::open())
 *  - manage the queue of transfert
 */
//! interface to manage every file transfert and informations
class   IFilePlugin
{
public:
    //! Return a new instance of File. No errors.
    virtual IFile* newFile(quint32 nodeId) = 0;
    //! Return an instance of File if the file is found on the server. 0 if not found or permition denied.
    virtual IFile* getFile(quint32 fileId) = 0;

    //! Return the full list of readable files. May be incomplete the first time. See SIGNAL(fileListUpdated(quint32)))
    //virtual const QList<IFile*> getFullFileList() const = 0;
    virtual const QHash<quint32,IFile*> getFullFileList() const = 0;
    //! Return the list of readable files of the nodeId. May be incomplete the first time. See SIGNAL(fileListUpdated(quint32)))
    virtual const QList<IFile*> getNodeFileList(quint32 nodeId) const = 0;
    virtual int countNodeFileList(quint32 nodeId) const = 0;
    //TODO: more filters
    //const QList<File*> getFileListByCTime(....); ByMtime By
};

Q_DECLARE_INTERFACE(IFilePlugin, "net.horus.Client.FilePluginInterface/1.0");

#endif // IFILEMANAGEMENT_H
