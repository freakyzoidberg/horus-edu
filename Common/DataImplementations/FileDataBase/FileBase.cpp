#include "FileBase.h"
#include "../../../Common/DataImplementations/FileDataBase/FileDataBase.h"
#include "../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.h"
#include "../../PluginManager.h"
#include "../../../Client/Plugins/FileBaseClient/FileNetworkPlugin.h"

#include <QDir>
#include <QSettings>

FileBase::FileBase(FileDataBase* file, FileNetworkPlugin* netPlugin) : File(file)
{
    _netPlugin = netPlugin;
    _file.setFileName("/tmp/"+QVariant(data()->id()).toString());
}

FileBase::~FileBase()
{
    qDebug() << "--------DELETE";
    close();
}

int FileBase::progress() const
{
    //TODO
    return 0;
}

void FileBase::connexionDisconnected()
{
    emit downloaded();
}

void FileBase::connectToServer(const QByteArray& key)
{
    qDebug() << "File::connectToServer(" << key.toHex() << ")";

    _socket.setProtocol(QSsl::SslV3);
    _socket.setPeerVerifyMode(QSslSocket::VerifyNone);

    connect(&_socket, SIGNAL(disconnected()), this, SLOT(connexionDisconnected()));
    QSettings settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
    _socket.connectToHostEncrypted(settings.value("Network/Server", "localhost").toString(),
                                     settings.value("Network/PortTransfert", 42042).toInt());
    _socket.waitForEncrypted();
    _socket.write(key);
    _socket.flush();
}

void FileBase::download(const QByteArray& key)
{
//    _socketPos = 0;
    _file.open(QIODevice::ReadWrite | QIODevice::Truncate);
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(connexionReadyRead()));

    connectToServer(key);
//    if (openMode() & WriteOnly)
//        connect(&_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(connexionBytesWritten(qint64)));
//    connect(this, SIGNAL(bytesWritten(qint64)), this, SLOT(fileBytesWritten(qint64)));
}

void FileBase::upload(const QByteArray& key)
{
}

void FileBase::connexionReadyRead()
{
    qDebug() << "File::connexionReadyRead()";

    QByteArray buff = _socket.readAll();
    if ( ! buff.length())
        return;

//    qint64 savedPos = _file.pos();
//    _file.seek(_socketPos);
    _file.write(buff);
    _file.flush();
//    _file.seek(savedPos);

//    _socketPos += buff.length();

//    emit readyRead();
}

void FileBase::connexionBytesWritten(qint64 len)
{
    qDebug() << "File::connexionByteWritten(" << len << ")";

//    if (file.atEnd())
//        return;

//    file.open(openMode());

//    qDebug() << _file.errorString();
//    qint64 savePos = _file.pos();
//    _file.seek(_socketPos);
    //_socketPos +=
    _socket.write(_file.read(8192));
//    if (file.atEnd())
  //      connexion.close();
//    _file.seek(savePos);
}


bool FileBase::open(OpenMode mode)
{
    bool ret = true;
    setOpenMode(mode);

    qDebug() << "File::open(" << openMode() << ")";

//    connect(this, SIGNAL(bytesWritten(qint64)), this, SLOT(fileBytesWritten(qint64)));

//    if ( ! _synchronized && (mode & ReadOnly))
//    {
//        _connecting = true;
//        //filePlugin->askForFileConnexion(fileData->id, mode);
//    }

//    if ( ! isOopen())
//        _file.setFileName("/tmp/"+QVariant( data()->id() ).toString());
    if ( ! isOopen())
    {
//        if ( ! isSynchronized())
//            ret = _file.open(mode | ReadWrite | Truncate);
//        else
            ret = _file.open(mode);
    }
    _file.seek(0);

//    emit synchronized();
    return ret;
}

bool FileBase::isOopen() const
{
    return _file.isOpen();
}

void FileBase::close()
{
    _file.close();
    _socket.close();
    //_synchronized = true;
    qDebug() << "File::close()";
}

qint64 FileBase::writeData(const char* data, qint64 maxSize)
{
    qDebug() << "File::writeData()";
    qint64 len = _file.write(data, maxSize);
//    file.flush();
//    fileBytesWritten(len);
//    emit bytesWritten(len);
    return len;
}

qint64 FileBase::readData(char* data, qint64 maxSize)
{
    qDebug() << "File::readData()";
    qint64 fileRead = _file.read(data, maxSize);
    if (fileRead < 0 && _socket.isOpen())
        return 0;
    return fileRead;
}

void FileBase::download()
{
    qDebug() << "File::download()";
    _netPlugin->askForDownload(data());
}

void FileBase::upload()
{
    qDebug() << "File::upload()";
    _netPlugin->askForUpload(data());
}
