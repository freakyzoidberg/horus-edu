#ifndef CLIENT_H
#define CLIENT_H

#include <QString>

namespace Horus
{
    namespace Server
    {
        class Client
        {
        public:
            Client();

            void            init();
            void            SendData(QString mod, void* data, int size);

        };
    }
}

#endif // CLIENT_H
