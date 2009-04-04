#ifndef COMMUNICATIONCONTAINER_H
#define COMMUNICATIONCONTAINER_H

#include "Defines.h"

class CommunicationContainer
{
 public:
    enum  msgType{ALIVE, FILE_DOWNLOAD, FILE_UPLOAD, CONFIG_GET, CONFIG_SET, MODULE_COMM};
    char  verCont[VERSION_SIZE];
    uint  sizeCont;
    void* content;
};

#endif // COMMUNICATIONCONTAINER_H
