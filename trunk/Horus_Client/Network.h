#ifndef NETWORK_H
#define NETWORK_H

#include "../Common/CommunicationContainer.h"

class Network
{
    public:
        Network();
        ~Network();
    private:
        CommunicationContainer   cC;
};

#endif // NETWORK_H
