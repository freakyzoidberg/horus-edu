#ifndef CLIENT_H
#define CLIENT_H

namespace Horus
{
    namespace Server
    {
        class Client
        {
        public:
            Client();

            void            init();
            void            SendData(std::string mod, void* data, int size);

        };
    };
};

#endif // CLIENT_H
