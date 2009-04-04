#ifndef COMMUNICATIONCONTAINER_H
#define COMMUNICATIONCONTAINER_H

#include ""

class CommunicationContainer
{
    char            modSrc [MODULE_NAME_SIZE];
    char            verSrc [MODULE_VERSION_SIZE];
    char            modDest[MODULE_NAME_SIZE];
    char            verCont[MODULE_VERSION_SIZE];
    ModuleContainer cont;
}

#endif // COMMUNICATIONCONTAINER_H
