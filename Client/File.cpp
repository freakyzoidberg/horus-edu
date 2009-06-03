#include "File.h"

File::File()
{
}

bool   File::needFile(const QString & fileName)
{
    return true;
}

bool   File::needFile(int id)
{
    return true;
}

int    File::getFileIdByName(const QString & fileName)
{
    return 42;
}

QString File::getNameById(int fileId)
{
    return QString("42");
}
