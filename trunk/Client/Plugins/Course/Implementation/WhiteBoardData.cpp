#include "WhiteBoardData.h"

WhiteBoardData::WhiteBoardData(FileDataPlugin *plugin, int fileId)
{
    fileData = plugin->getFile(fileId);
    qDebug() << "Whiteboard: " << fileData->file()->readAll();
}
