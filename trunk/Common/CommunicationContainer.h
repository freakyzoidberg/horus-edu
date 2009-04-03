#ifndef COMMUNICATIONCONTAINER_H
#define COMMUNICATIONCONTAINER_H

#include <string>
#include "ModuleContainer.h"

class CommunicationContainer
{
    public:
        std::string     mSource;
        std::string     vSource;
        std::string     vDist;
        ModuleContainer mC;
}

#endif // COMMUNICATIONCONTAINER_H
