#ifndef SERVER_H
#define SERVER_H

namespace Horus
{
    namespace Server
    {
        class Server
        {
        public:
            std::list<Module> mods;

            const Server* getInstance();

            void start();
            void stop();

            void*           DBQuery();
            Module&         getModule(std::string name);

        private:
            Server();
            Server* singleton;
        };
    }
}

#endif // SERVER_H
