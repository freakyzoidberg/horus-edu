#ifndef MODULECONTAINER_H
#define MODULECONTAINER_H

#include "Defines.h"

class ModuleContainer
{
 public:
    char modSrc [MODULE_NAME_SIZE];
    char verSrc [MODULE_VERSION_SIZE];
    char modDest[MODULE_NAME_SIZE];
    char verCont[MODULE_VERSION_SIZE];
    uint  sizeCont;
    void *content;
};

#endif // MODULECONTAINER_H
