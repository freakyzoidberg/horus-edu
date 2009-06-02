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

    //TODO: if file not opened from the begining
    connexionPos = 0;

    connect(connexion, SIGNAL(readyRead()), this, SLOT(connexionReadyRead()));

    //TODO: get in settings
    //TODO: write only if no read needed
    connexion->setProtocol(QSsl::SslV3);
    //TODO later: For test
    connexion->setPeerVerifyMode(QSslSocket::VerifyNone);
    connexion->connectToHostEncrypted("localhost", 42042, QIODevice::ReadWrite);
    connexion->waitForEncrypted();
    connexion->write(key);
    connexion->flush();

    connect(connexion, SIGNAL(bytesWritten(qint64)), this, SLOT(connexionBytesWritten(qint64)));

    emit connexionOpened();
}

void NetFile::connexionReadyRead()
{
    qDebug() << "NetFile::connexionReadyRead()";
    QByteArray buff = connexion->readAll();

    localFile.seek(connexionPos);
    localFile.write(buff);
    localFile.seek(localFilePos);

    emit readyRead();
}

void NetFile::connexionBytesWritten(qint64 len)
{
    qDebug() << "NetFile::connexionByteWritten(" << len << ")";
    emit bytesWritten(len);
}

qint64 NetFile::pos() const
{
    return localFilePos;
}

NetFile::NetFile(const CommFileInfo& _info)
{
    info = _info;
    connexion = 0;
}

NetFile::~NetFile()
{
    close();
}

int NetFile::getProgress()
{
    //TODO
    return 0;
}

const CommFileInfo& NetFile::getInfo()
{
    return info;
}

bool NetFile::open(OpenMode mode)
{
    //TODO: if (not already downloaded || mode & WriteOnly)
    FileManager::globalInstance()->getFileConnexion(info.id, mode);

    //TODO: if ( not already downloaded && ! serverFile)
        //return false;

    localFile.setFileName("/tmp/" + QVariant(info.id).toString());
    return localFile.open(mode);
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
    qint64 len = localFile.read(data, maxSize);
    localFilePos += len;
    return len;
}

qint64 NetFile::writeData(const char* data, qint64 maxSize)
{
    qint64 lenWrite = connexion->write(data, maxSize);
    connexionPos += lenWrite;
    lenWrite = localFile.write(data, lenWrite);
    localFilePos += lenWrite;
    return lenWrite;
}

