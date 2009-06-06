#include "File.h"
#include "FileManager.h"

#include <QApplication>

File::File(const CommFileInfo& _info)
{
    info = _info;
    synchronized = false;
    connecting = false;
    moveToThread(QApplication::instance()->thread());
}

File::~File()
{
    qDebug() << "--------DELETE";
    close();
}

int File::getProgress() const
{
    //TODO
    return 0;
}

void File::connexionDisconnected()
{
    synchronized = true;
    emit fileSynchronized();
}

bool File::isSynchronized() const
{
    return synchronized;
}

const CommFileInfo& File::getInfo() const
{
    return info;
}

const QString File::getLocalFileName() const
{
     return "/tmp/" + QVariant(info.id).toString();
}

void File::setFileName(const QString& name)
{
    info.fileName = name;
}
void File::updateFileInfo(const CommFileInfo& _info)
{
    qDebug() << "File::updateFileInfo(" << _info << ")";

    quint32 oldId = info.id;

    if (info != _info)
    {
        info = _info;
        emit fileInfoUpdated();
    }

    if (info.id != oldId)
        file.rename(getLocalFileName());
}

void File::connexionAuthorized(const QByteArray& key)
{
    qDebug() << "File::connexionAuthorized(" << key.toHex() << ")";

    //TODO: if file not opened from the begining
    connexionPos = 0;

    //TODO: get in settings
    //TODO: write only if no read needed
    connexion.setProtocol(QSsl::SslV3);
    //TODO later: For test
    connexion.setPeerVerifyMode(QSslSocket::VerifyNone);
    connect(&connexion, SIGNAL(disconnected()), this, SLOT(connexionDisconnected()));
    connexion.connectToHostEncrypted("localhost", 42042, QIODevice::ReadWrite);
    connexion.waitForEncrypted();
    connect(&connexion, SIGNAL(readyRead()), this, SLOT(connexionReadyRead()));
    if (openMode() & WriteOnly)
        connect(&connexion, SIGNAL(bytesWritten(qint64)), this, SLOT(connexionBytesWritten(qint64)));
    connect(this, SIGNAL(bytesWritten(qint64)), this, SLOT(fileBytesWritten(qint64)));
    connecting = false;
    connexion.write(key);
    connexion.flush();
}

void File::connexionReadyRead()
{
    qDebug() << "File::connexionReadyRead()";

    QByteArray buff = connexion.readAll();
    if ( ! buff.length())
        return;

    qint64 savedPos = file.pos();
    file.seek(connexionPos);
    file.write(buff);
    file.flush();
    file.seek(savedPos);

    connexionPos += buff.length();

    emit readyRead();
}

void File::connexionBytesWritten(qint64 len)
{
    qDebug() << "File::connexionByteWritten(" << len << ")";

//    if (file.atEnd())
//        return;

//    file.open(openMode());

    qDebug() << file.errorString();
    qint64 savePos = file.pos();
    file.seek(connexionPos);
    connexionPos += connexion.write(file.read(len));
//    if (file.atEnd())
  //      connexion.close();
    file.seek(savePos);
}


bool File::open(OpenMode mode)
{
    bool ret = true;
    setOpenMode(mode);

    qDebug() << "File::open(" << openMode() << ")";

    connect(this, SIGNAL(bytesWritten(qint64)), this, SLOT(fileBytesWritten(qint64)));

    if ( ! synchronized && (mode & ReadOnly))
    {
        connecting = true;
        FileManager::instance()->askForFileConnexion(info.id, mode);
    }

    if ( ! isOopen())
        file.setFileName(getLocalFileName());
    if ( ! isOopen())
    {
        if ( ! isSynchronized())
            ret = file.open(mode | ReadWrite | Truncate);
        else
            ret = file.open(mode);
    }
    file.seek(0);

    emit fileSynchronized();
    return ret;
}

bool File::isOopen() const
{
    return file.isOpen();
}

void File::close()
{
    file.close();
    connexion.close();
    this->synchronized = true;
    qDebug() << "File::close()";
}

qint64 File::writeData(const char* data, qint64 maxSize)
{
    qDebug() << "File::writeData()";
    qint64 len = file.write(data, maxSize);
//    file.flush();
//    fileBytesWritten(len);
    emit bytesWritten(len);
    return len;
}

qint64 File::readData(char* data, qint64 maxSize)
{
    qDebug() << "File::readData()";
    qint64 fileRead = file.read(data, maxSize);
    if (fileRead < 0 && connexion.isOpen())
        return 0;
    return fileRead;
}

void File::fileBytesWritten(qint64)
{
    disconnect(this, SLOT(fileBytesWritten(qint64)));
    synchronize();
}

void File::synchronize()
{
    qDebug() << "File::synchronize()";

    if (connexion.isOpen())
        return connexionBytesWritten(0);

    if (connecting)
        return;
    connecting = true;
    FileManager::instance()->askForFileConnexion(info.id, openMode());
}
