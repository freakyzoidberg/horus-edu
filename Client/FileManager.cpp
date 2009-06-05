#include "FileManager.h"
#include "../Common/CommFile.h"
#include <QApplication>
#include "ThreadNetwork.h"

//FileManager FileManager::instance;

FileManager::FileManager()
{
    moveToThread(QApplication::instance()->thread());
    tmpNewFile = 0;
    haveFullList = false;
}

FileManager* FileManager::instance()
{
    static FileManager i;
    return &i;
}

IFile* FileManager::newFile(quint32 nodeId)
{
    if (tmpNewFile)
    {
    //TODO: try to change this way
        qDebug() << "only one file can be created in the same time, please wait.";
        return 0;
    }

    CommFileInfo info;
    info.nodeId = nodeId;
    tmpNewFile = new File(info);
    emit fileListUpdated();
    emit nodeFileListUpdated(nodeId);
    return tmpNewFile;
}

IFile* FileManager::getFile(quint32 fileId)
{
    if ( ! fileHash.contains(fileId))
    {
        CommFileInfo info;
        info.id = fileId;
        fileHash[ fileId ] = new File(info);

        emit fileListUpdated();

        // update the fileInfo
//        askForFileInfo(fileId);
    }

    return fileHash[ fileId ];
}

void FileManager::askForFileInfo(quint32 fileId) const
{
    CommFile packet;
    packet.method = CommFile::STAT_FILE;
    packet.fileInfo.id = fileId;
    QApplication::postEvent(ThreadNetwork::getInstance(), new SendPacketEvent(packet.getPacket()));
}

void FileManager::askForFileFullList() const
{
    if (haveFullList)
        return;

    CommFile packet;
    packet.method = CommFile::USER_LIST;
    QApplication::postEvent(ThreadNetwork::getInstance(), new SendPacketEvent(packet.getPacket()));
}

void FileManager::askForFileConnexion(quint32 fileId, QIODevice::OpenMode mode) const
{
    CommFile packet;
    if (fileId)
        packet.method = CommFile::ACCESS_FILE;
    else
        packet.method = CommFile::NEW_FILE;
    packet.mode = mode;
    packet.fileInfo.id = fileId;
    QApplication::postEvent(ThreadNetwork::getInstance(), new SendPacketEvent(packet.getPacket()));
}

const QHash<quint32,IFile*> FileManager::getFullFileList() const
{
    askForFileFullList();
    return fileHash;
}
/*
const QList<IFile*> FileManager::getFullFileList() const
{
    askForFileFullList();
    QList<IFile*> list;
    for (QHash<quint32,File*>::const_iterator i = fileHash.begin(); i != fileHash.end(); ++i)
        list.append(*i);
}
*/
const QList<IFile*> FileManager::getNodeFileList(quint32 nodeId) const
{
    QList<IFile*> list;
    for (QHash<quint32,IFile*>::const_iterator i = fileHash.begin(); i != fileHash.end(); ++i)
        if ((*i)->getInfo().nodeId == nodeId)
            list.append(*i);
}

void FileManager::receiveFilePacket(QByteArray p)
{
    CommFile packet(p);
    if (packet.error)
    {
        qDebug() << "FileManager::receiveFilePacket error:" << packet;
        return;
    }

    if (packet.method == CommFile::NEW_FILE && tmpNewFile)
    {
        fileHash[ tmpNewFile->info.id ] = tmpNewFile;
        tmpNewFile = 0;
    }

    if (packet.method == CommFile::ACCESS_FILE
     || packet.method == CommFile::STAT_FILE
     || packet.method == CommFile::NEW_FILE)
    {
        File* file = (File*)getFile(packet.fileInfo.id);
        file->updateFileInfo(packet.fileInfo);

        if (packet.method == CommFile::ACCESS_FILE
         || packet.method == CommFile::NEW_FILE)
            file->connexionAuthorized(packet.key);
    }

    else if (packet.method == CommFile::NODE_LIST
          || packet.method == CommFile::USER_LIST)
    {
        //TODO: emmit less signal: only if a real change append on the viewed nodes

        for (QList<CommFileInfo>::const_iterator i = packet.fileList.begin(); i != packet.fileList.end(); ++i)
        {
            ((File*)getFile((*i).id))->updateFileInfo(*i);
            emit nodeFileListUpdated((*i).nodeId);
        }
        if (packet.method == CommFile::USER_LIST)
            haveFullList = true;
        emit fileListUpdated();
    }

    else
        qDebug() << "FileManager::receiveFilePacket invalid packet" << packet;
}
