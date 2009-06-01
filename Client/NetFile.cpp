#include "NetFile.h"

QHash<quint32,NetFile*> NetFile::fileList;

NetFile* NetFile::newFile(quint32 nodeId)
{
    //TODO
    return 0;
}

NetFile* NetFile::getFile(quint32 fileId)
{
    //TODO
    if (fileList.contains(fileId))
        return fileList[fileId];

    return new NetFile(fileId);
}

NetFile::NetFile(quint32 fileId)
{
    infoLock.lock();
    syncLock.lock();
}

NetFile::~NetFile()
{
}

bool NetFile::isInfoAvailable()
{
    return waitForInfoAvailable(0);
}

bool NetFile::isSynchronized()
{
    return waitForSynchronized(0);
}

int NetFile::getProgress()
{
    if (isSynchronized())
        return 100;
    if (isInfoAvailable())
        return 10;
    return 1;
}

const CommFileInfo& NetFile::getInfo()
{
    waitForInfoAvailable();
    return info;
}

bool NetFile::waitForInfoAvailable(int timeout)
{
    if ( ! infoLock.tryLock(timeout))
        return false;

    infoLock.unlock();
    return true;
}

bool NetFile::waitForSynchronized(int timeout)
{
    if ( ! syncLock.tryLock(timeout))
        return false;

    syncLock.unlock();
    return true;
}

qint64 NetFile::readData(char* data, qint64 maxSize)
{
    return localFile.read(data, maxSize);
}

qint64 NetFile::writeData(const char* data, qint64 maxSize)
{
    return localFile.write(data, maxSize);
}

