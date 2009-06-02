#include "NetFile.h"

#include "FileManager.h"

QHash<quint32,NetFile*> NetFile::fileList;

NetFile* NetFile::newFile(quint32 nodeId)
{
    CommFileInfo info;
    info.nodeId = nodeId;
    
    NetFile* file = new NetFile(info);
    //TODO: delete if not used
    return file;
}

NetFile* NetFile::getFile(quint32 fileId)
{
    if ( ! fileList.contains(fileId))
    {
        CommFileInfo info;
        info.id = fileId;
        fileList[ fileId ] = new NetFile(info);
    }

    //FileManager::globalInstance()->getFileInfo(fileId);

    return fileList[ fileId ];
}

void NetFile::updateFileInfo(const CommFileInfo& _info)
{
    qDebug() << "NetFile::updateFileInfo(" << _info << ")";
    info = _info;
    emit fileInfoUpdated();
}

void NetFile::connexionAuthorized(const QByteArray& key)
{
    qDebug() << "NetFile::connexionAuthorized(" << key.toHex() << ")";

    connexion = new QSslSocket(this);

    //TODO: get in settings
    //TODO: write only if no read needed
    connexion->setProtocol(QSsl::SslV3);
    //TODO later: For test
    connexion->setPeerVerifyMode(QSslSocket::VerifyNone);
    connexion->connectToHostEncrypted("localhost", 42042, QIODevice::ReadWrite);
    connexion->waitForEncrypted();
    connexion->write(key);
    connexion->flush();
}

NetFile::NetFile(const CommFileInfo& _info)
{
    info = _info;
    connexion = 0;
}

NetFile::~NetFile()
{
}
/*
bool NetFile::isSynchronized()
{
    return waitForSynchronized(0);
}
*//*
int NetFile::getProgress()
{
    if (isSynchronized())
        return 100;
    if (isInfoAvailable())
        return 10;
    return 1;
}
*/
const CommFileInfo& NetFile::getInfo()
{
    return info;
}
/*
bool NetFile::waitForSynchronized(int timeout)
{
    if ( ! syncLock.tryLock(timeout))
        return false;

    syncLock.unlock();
    return true;
}
*/
bool NetFile::open(OpenMode mode)
{
    //TODO: if (not already downloaded || mode & WriteOnly)
    FileManager::globalInstance()->getFileConnexion(info.id, mode);

    //TODO: if ( not already downloaded && ! serverFile)
        //return false;

    return true;//localFile.open(mode);
}

void NetFile::close()
{
    localFile.close();
    if (connexion)
    {
        connexion->close();
        delete connexion;
    }
}

qint64 NetFile::readData(char* data, qint64 maxSize)
{
    return localFile.read(data, maxSize);
}

qint64 NetFile::writeData(const char* data, qint64 maxSize)
{
    qint64 lenWrite = maxSize;//serverFile.write(data, maxSize);
    return localFile.write(data, lenWrite);
}

