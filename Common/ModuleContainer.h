#ifndef MODULECONTAINER_H
#define MODULECONTAINER_H

#include "Defines.h"

/*!
 * If the "messageType" of the "CommunicationContainer" is "MODULE_COMM"
 * there is this class inside "content".
 * it's for the comunication between a module client and a module server
 */
class ModuleContainer
{
 public:
    char modSrc [MODULE_NAME_SIZE];
    char verSrc [MODULE_VERSION_SIZE];
    char modDest[MODULE_NAME_SIZE];
    char verCont[MODULE_VERSION_SIZE];

    int  sizeCont;
    void *content;
};

#endif // MODULECONTAINER_H
