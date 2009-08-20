#include "FileBase.h"
#include "../../../Common/FileDataPlugin.h"

#include <QDir>
#include <QSettings>

FileBase::FileBase(FileDataBasePlugin* _plugin, FileDataBase* _file)
{
    filePlugin = _plugin;
    fileData = _file;
    synchronized = false;
    connecting = false;
}

FileBase::~FileBase()
{
    qDebug() << "--------DELETE";
    close();
}

int FileBase::getProgress() const
{
    //TODO
    return 0;
}

void FileBase::connexionDisconnected()
{
    synchronized = true;
    emit fileSynchronized();
}

bool FileBase::isSynchronized() const
{
    return synchronized;
}

void FileBase::connexionAuthorized(const QByteArray& key)
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
    QSettings settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
    connexion.connectToHostEncrypted(settings.value("Network/Server", "localhost").toString(),
                                     settings.value("Network/PortTransfert", 42042).toInt(),
                                     QIODevice::ReadWrite);
    connexion.waitForEncrypted();
    connect(&connexion, SIGNAL(readyRead()), this, SLOT(connexionReadyRead()));
    if (openMode() & WriteOnly)
        connect(&connexion, SIGNAL(bytesWritten(qint64)), this, SLOT(connexionBytesWritten(qint64)));
    connect(this, SIGNAL(bytesWritten(qint64)), this, SLOT(fileBytesWritten(qint64)));
    connecting = false;
    connexion.write(key);
    connexion.flush();
}

void FileBase::connexionReadyRead()
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

void FileBase::connexionBytesWritten(qint64 len)
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


bool FileBase::open(OpenMode mode)
{
    bool ret = true;
    setOpenMode(mode);

    qDebug() << "File::open(" << openMode() << ")";

    connect(this, SIGNAL(bytesWritten(qint64)), this, SLOT(fileBytesWritten(qint64)));

    if ( ! synchronized && (mode & ReadOnly))
    {
        connecting = true;
        fileManagement->askForFileConnexion(info.id, mode);
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

bool FileBase::isOopen() const
{
    return file.isOpen();
}

void FileBase::close()
{
    file.close();
    connexion.close();
    this->synchronized = true;
    qDebug() << "File::close()";
}

qint64 FileBase::writeData(const char* data, qint64 maxSize)
{
    qDebug() << "File::writeData()";
    qint64 len = file.write(data, maxSize);
//    file.flush();
//    fileBytesWritten(len);
    emit bytesWritten(len);
    return len;
}

qint64 FileBase::readData(char* data, qint64 maxSize)
{
    qDebug() << "File::readData()";
    qint64 fileRead = file.read(data, maxSize);
    if (fileRead < 0 && connexion.isOpen())
        return 0;
    return fileRead;
}

void FileBase::fileBytesWritten(qint64)
{
    disconnect(this, SLOT(fileBytesWritten(qint64)));
    synchronize();
}

void FileBase::synchronize()
{
    qDebug() << "File::synchronize()";

    if (connexion.isOpen())
        return connexionBytesWritten(0);

    if (connecting)
        return;
    connecting = true;
    fileManagement->askForFileConnexion(info.id, openMode());
}
