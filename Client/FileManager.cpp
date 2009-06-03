#include "FileManager.h"
#include "../Common/CommFile.h"
#include <QApplication>
#include "ThreadNetwork.h"

FileManager FileManager::instance;

FileManager::FileManager()
{
    tmpNewFile = 0;
}

FileManager* FileManager::globalInstance()
{
    return &instance;
}

NetFile* FileManager::newFile(quint32 nodeId)
{
    if (tmpNewFile)
    {
    //TODO: change this way
        qDebug() << "only one file can be created in the same time, please wait.";
        return 0;
    }

    CommFileInfo info;
    info.nodeId = nodeId;
    tmpNewFile = new NetFile(info);
    return tmpNewFile;
}

NetFile* FileManager::getFile(quint32 fileId)
{
    if ( ! fileList.contains(fileId))
    {
        CommFileInfo info;
        info.id = fileId;
        fileList[ fileId ] = new NetFile(info);
        // update the fileInfo
        getFileInfo(fileId);
    }

    return fileList[ fileId ];
}

void FileManager::getFileInfo(quint32 fileId)
{
    CommFile packet;
    packet.method = CommFile::STAT_FILE;
    packet.fileInfo.id = fileId;
    QApplication::postEvent(ThreadNetwork::getInstance(), new SendPacketEvent(packet.getPacket()));
}

void FileManager::getFileConnexion(quint32 fileId, QIODevice::OpenMode mode)
{
    CommFile packet;
    packet.method = CommFile::ACCESS_FILE;
    packet.mode = mode;
    packet.fileInfo.id = fileId;
    QApplication::postEvent(ThreadNetwork::getInstance(), new SendPacketEvent(packet.getPacket()));
}
/*
const QList<CommFileInfo> FileManager::getUserFileList()
{TODO}
*/
/*
const QList<CommFileInfo> FileManager::getNodeFileList(quint32 nodeId)
{TODO}
*/
void FileManager::receiveFilePacket(QByteArray& p)
{
    CommFile packet(p);
    if (packet.error)
    {
        qDebug() << "FileManager::receiveFilePacket error:" << packet;
        return;
    }

    if (packet.method == CommFile::NEW_FILE && tmpNewFile)
    {
        fileList[ tmpNewFile->info.id ] = tmpNewFile;
        tmpNewFile = 0;
    }

    if (packet.method == CommFile::ACCESS_FILE
     || packet.method == CommFile::STAT_FILE
     || packet.method == CommFile::NEW_FILE)
    {
        NetFile* file = getFile(packet.fileInfo.id);

        file->updateFileInfo(packet.fileInfo);
        if (packet.method == CommFile::ACCESS_FILE)
            file->connexionAuthorized(packet.key);
    }
    else
        qDebug() << "FileManager::receiveFilePacket not yet:" << packet;
}
