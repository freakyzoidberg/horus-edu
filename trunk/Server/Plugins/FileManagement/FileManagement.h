#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <QtSql>

#include "ThreadFiles.h"

#include "../../../Common/Defines.h"
#include "../IServer.h"
#include "../IServerPlugin.h"

//! a Server Plugin to test the communication between a Client Plugin and a Server Plugin
class FileManagement : public IServerPlugin
{
  Q_OBJECT
  Q_INTERFACES(IServerPlugin)

  typedef void (FileManagement::*requestFunction)(quint32 userId, const QVariantHash& request, PluginPacket& response);

public:
    FileManagement();



    // IServerPlugin
    inline const QByteArray name()    const { return "FileManagement"; }
    inline const QByteArray version() const { return "0.1"; }
    bool start();
    void recvPacket(quint32 userId, const PluginPacket&);



    //Maybe create a new IFileManagementServerPlugin if needed with these methods
    //! return the FileInfo of fileId
    //const FileInfo* getFileInfo(quint32 fileId);
    //! return the list of FileInfo of the node
    //const QList<FileInfo> getNodeList(quint32 nodeId);
    //! return the list of FileInfo of the user
    //const QList<FileInfo> getUserList(quint32 userId);
    //! insert new file
    //void insertNewFile(FileInfo& file);
    //! true if the file exist
    //bool fileExist(quint32 fileId);
    //! true if the user userId can read the file fileId
    //bool userCanReadFile(quint32 userId, quint32 fileId);
    //! true if the user userId can write the file fileId
    //bool userCanWriteFile(quint32 userId, quint32 fileId);
    //! true if the user userId can list the node nodeId
    //bool userCanListNode(quint32 userId, quint32 nodeId);
    //! true if the user userId can change the node nodeId (create/delete)
    //bool userCanChangeNode(quint32 userId, quint32 nodeId);



private:
    //! functions for each request
    /*! called by recvPacket */
    QHash<QByteArray,requestFunction> requestFunctions;

    //! if request is not found
    void unknownRequest(quint32 userId, const QVariantHash& request,PluginPacket& response);

//    void stat          (quint32 userId, const QVariantHash& request,PluginPacket& response);
    void createRequest   (quint32 userId, const QVariantHash& request,PluginPacket& response);
    void accessRequest   (quint32 userId, const QVariantHash& request,PluginPacket& response);
//    void listNode      (quint32 userId, const QVariantHash& request,PluginPacket& response);
//    void listUser      (quint32 userId, const QVariantHash& request,PluginPacket& response);
    void listRequest     (quint32 userId, const QVariantHash& request,PluginPacket& response);

    ThreadFiles* thread;
};

#endif // FILEMANAGEMENT_H
