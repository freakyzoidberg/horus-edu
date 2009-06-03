#include "NetFile.h"

#include "FileManager.h"

void NetFile::updateFileInfo(const CommFileInfo& _info)
{
    qDebug() << "NetFile::updateFileInfo(" << _info << ")";
    if (info != _info)
    {
        info = _info;
        setFileName("/tmp/" + QVariant(info.id).toString());
        emit fileInfoUpdated();
    }
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

    qint64 savePos = pos();

    seek(connexionPos);
    write(buff);
    seek(savePos);

    emit readyRead();
}

void NetFile::connexionBytesWritten(qint64 len)
{
    qDebug() << "NetFile::connexionByteWritten(" << len << ")";
    emit bytesWritten(len);
}

NetFile::NetFile(const CommFileInfo& _info)
{
    info = _info;
    connexion = 0;
    synchronized = false;
    if (info.id)
        setFileName("/tmp/" + QVariant(info.id).toString());
}

NetFile::~NetFile()
{
    close();
}

int NetFile::getProgress() const
{
    //TODO
    return 0;
}

bool NetFile::isSynchronized() const
{
    return synchronized;
}

const CommFileInfo& NetFile::getInfo() const
{
    return info;
}

bool NetFile::open(OpenMode mode)
{
    if ( ! synchronized || mode & WriteOnly) // if not syncronized or open in write mode
        FileManager::globalInstance()->getFileConnexion(info.id, mode);

    return QFile::open(mode);
}

void NetFile::close()
{
    QFile::close();
    if (connexion)
    {
        connexion->close();
        delete connexion;
    }
}

//qint64 NetFile::readData(char* data, qint64 maxSize)
//{
//    return QFile::readData(data, maxSize);
//}

qint64 NetFile::writeData(const char* data, qint64 maxSize)
{
    synchronized = false;
    return QFile::writeData(data, maxSize);
//    qint64 lenWrite = connexion->write(data, maxSize);
//    connexionPos += lenWrite;
}
