#ifndef FILEMANAGMENT_H
#define FILEMANAGMENT_H

#include <QList>
#include "../Common/FileInfo.h"

class FileManagment
{
public:
    FileManagment();

    //! return the FileInfo of fileId
    const FileInfo& getFileInfo       (quint32 fileId);
    //! return the list of FileInfo of the node
    const QList<FileInfo> getNodeList (quint32 nodeId);
    //! return the list of FileInfo of the user
    const QList<FileInfo> getUserList (quint32 userId);
    //! insert new file
    void insertNewFile(FileInfo& file);

    //! true if the file exist
    bool                fileExist         (quint32 fileId);
    //! true if the user userId can read the file fileId
    bool                userCanReadFile   (quint32 userId, quint32 fileId);
    //! true if the user userId can write the file fileId
    bool                userCanWriteFile  (quint32 userId, quint32 fileId);

    //! true if the user userId can list the node nodeId
    bool                userCanListNode   (quint32 userId, quint32 nodeId);
    //! true if the user userId can change the node nodeId (create/delete)
    bool                userCanChangeNode (quint32 userId, quint32 nodeId);

private:
    FileInfo            lastFileInfo;
};

#endif // FILEMANAGMENT_H
