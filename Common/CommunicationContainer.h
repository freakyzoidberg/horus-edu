#ifndef COMMUNICATIONCONTAINER_H
#define COMMUNICATIONCONTAINER_H

#include "Defines.h"

class CommunicationContainer
{
 public:
    char            modSrc [MODULE_NAME_SIZE];
    char            verSrc [MODULE_VERSION_SIZE];
    char            modDest[MODULE_NAME_SIZE];
    char            verCont[MODULE_VERSION_SIZE];
    ModuleContainer cont;
}

#endif // COMMUNICATIONCONTAINER_H
