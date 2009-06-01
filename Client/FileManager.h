#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>

#include "NetFile.h"

class FileManager
{
public:
    static FileManager* globalInstance();

    void enQueue(NetFile* file);

private:
    FileManager();
    static FileManager* instance;
};

#endif // FILEMANAGER_H
