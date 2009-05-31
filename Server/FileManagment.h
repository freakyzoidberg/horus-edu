#ifndef FILEMANAGMENT_H
#define FILEMANAGMENT_H

#include <QList>
#include "../Common/CommFileInfo.h"

class FileManagment
{
public:
    FileManagment();

    //! return the CommFileInfo of fileId
    const CommFileInfo& getFileInfo       (quint32 fileId);
    //! return the list of CommFileInfo of the node
    const QList<CommFileInfo> getNodeList (quint32 nodeId);
    //! return the list of CommFileInfo of the user
    const QList<CommFileInfo> getUserList (quint32 userId);
    //! insert new file
    void insertNewFile(CommFileInfo& file);

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
    CommFileInfo        lastFileInfo;
};

#endif // FILEMANAGMENT_H
