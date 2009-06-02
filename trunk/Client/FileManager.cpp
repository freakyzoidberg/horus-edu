#include "FileManager.h"
#include "../Common/CommFile.h"
#include <QApplication>
#include "ThreadNetwork.h"

FileManager* FileManager::instance = 0;

FileManager::FileManager()
{
    inUse = false;
}

FileManager* FileManager::globalInstance()
{
    if ( ! instance)
        instance = new FileManager;
    return instance;
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
{
}
*//*
const QList<CommFileInfo> FileManager::getNodeFileList(quint32 nodeId)
{
}
*/
void FileManager::receiveFilePacket(QByteArray& p)
{
    CommFile packet(p);
    if (packet.error)
    {
        qDebug() << "FileManager::receiveFilePacket error:" << packet;
        return;
    }

    if (packet.method == CommFile::ACCESS_FILE || packet.method == CommFile::STAT_FILE)
    {
        NetFile* file = NetFile::getFile(packet.fileInfo.id);
        file->updateFileInfo(packet.fileInfo);
        if (packet.method == CommFile::ACCESS_FILE)
            file->connexionAuthorized(packet.key);
    }
    else
        qDebug() << "FileManager::receiveFilePacket not yet:" << packet;
}
