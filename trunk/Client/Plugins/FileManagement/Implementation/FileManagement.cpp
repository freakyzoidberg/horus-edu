#include "FileManagement.h"

Q_EXPORT_PLUGIN2(FileManagement,FileManagement)

FileManagement::FileManagement()
{
    tmpNewFile = 0;
    haveFullList = false;
}

IFile* FileManagement::newFile(quint32 nodeId)
{
    if (tmpNewFile)
    {
    //TODO: try to change this way
        qDebug() << "only one file can be created in the same time, please wait.";
        return 0;
    }

    FileInfo info;
    info.nodeId = nodeId;
    tmpNewFile = new File(this, info);
    tmpNewFile->setObjectName("IFile");
    //emit fileListUpdated();
    //emit nodeFileListUpdated(nodeId);
    return tmpNewFile;
}

IFile* FileManagement::getFile(quint32 fileId)
{
    if ( ! fileHash.contains(fileId))
    {
        FileInfo info;
        info.id = fileId;
        IFile* file = new File(this, info);
        file->setObjectName("IFile");
        fileHash[ fileId ] = file;

        //emit fileListUpdated();

        // update the fileInfo
//        askForFileInfo(fileId);
    }

    return fileHash[ fileId ];
}

void FileManagement::askForFileInfo(quint32 fileId) const
{
    network->sendPacket(PluginPacket("FileManagement", "list"));
}

void FileManagement::askForFileFullList() const
{
    if (haveFullList)
        return;

    network->sendPacket(PluginPacket("FileManagement", "list"));
}

void FileManagement::askForFileConnexion(quint32 fileId, QIODevice::OpenMode mode) const
{
//    CommFile packet;
//    if (fileId)
//        packet.method = CommFile::ACCESS_FILE;
//    else
//        packet.method = CommFile::NEW_FILE;
//    packet.mode = mode;
//    packet.fileInfo.id = fileId;
//    QApplication::postEvent(ThreadNetwork::getInstance(), new SendPacketEvent(packet.getPacket()));
}

const QHash<quint32,IFile*> FileManagement::getFullFileList() const
{
    askForFileFullList();
    return fileHash;
}

const QList<IFile*> FileManagement::getNodeFileList(quint32 nodeId) const
{
    QList<IFile*> list;
    for (QHash<quint32,IFile*>::const_iterator i = fileHash.begin(); i != fileHash.end(); ++i)
        if ((*i)->getInfo().nodeId == nodeId)
            list.append(*i);
    return list;
}

int FileManagement::countNodeFileList(quint32 nodeId) const
{
    int n = 0;
    for (QHash<quint32,IFile*>::const_iterator i = fileHash.begin(); i != fileHash.end(); ++i)
        if ((*i)->getInfo().nodeId == nodeId)
            n++;
    return n;
}

void FileManagement::recvPacket(const PluginPacket&)
{
//    CommFile packet(p);
//    if (packet.error)
//    {
//        qDebug() << "FileManagement::receiveFilePacket error:" << packet;
//        return;
//    }
//
//    if (packet.method == CommFile::NEW_FILE && tmpNewFile)
//    {
//        fileHash[ tmpNewFile->info.id ] = tmpNewFile;
//        tmpNewFile = 0;
//    }
//
//    if (packet.method == CommFile::ACCESS_FILE
//     || packet.method == CommFile::STAT_FILE
//     || packet.method == CommFile::NEW_FILE)
//    {
//        File* file = (File*)getFile(packet.fileInfo.id);
//        file->updateFileInfo(packet.fileInfo);
//
//        if (packet.method == CommFile::ACCESS_FILE
//         || packet.method == CommFile::NEW_FILE)
//            file->connexionAuthorized(packet.key);
//    }
//
//    else if (packet.method == CommFile::NODE_LIST
//          || packet.method == CommFile::USER_LIST)
//    {
//        //TODO: emmit less signal: only if a real change append on the viewed nodes
//
//        for (QList<FileInfo>::const_iterator i = packet.fileList.begin(); i != packet.fileList.end(); ++i)
//        {
//            ((File*)getFile((*i).id))->updateFileInfo(*i);
//            emit nodeFileListUpdated((*i).nodeId);
//        }
//        if (packet.method == CommFile::USER_LIST)
//            haveFullList = true;
//        emit fileListUpdated();
//    }
//
//    else
//        qDebug() << "FileManagement::receiveFilePacket invalid packet" << packet;
}
