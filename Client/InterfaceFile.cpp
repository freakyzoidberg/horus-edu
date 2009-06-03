#include "InterfaceFile.h"

InterfaceFile::InterfaceFile()
{
}

bool   InterfaceFile::needFile(const QString & fileName)
{
    return true;
}

bool   InterfaceFile::needFile(int id)
{
    return true;
}

int    InterfaceFile::getFileIdByName(const QString & fileName)
{
    return 42;
}

QString InterfaceFile::getNameById(int fileId)
{
    return QString("42");
}
