#ifndef WHITEBOARDDATA_H
#define WHITEBOARDDATA_H

#include "../../../../Common/FileDataPlugin.h"
#include "../../../../Common/FileData.h"

class WhiteBoardData
{
public:
    WhiteBoardData(FileDataPlugin *plugin, int fileId);

private:
    FileData *fileData;
};

#endif // WHITEBOARDDATA_H
