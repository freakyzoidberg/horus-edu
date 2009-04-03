#ifndef SERVER_H
#define SERVER_H

#include <QList>

#include "module.h"

namespace Horus
{
    namespace Server
    {
        class Server
        {
        public:
            QList<Module> mods;
/*
            const Server* getInstance();

            void start();
            void stop();

            void*           DBQuery();
            Module&         getModule(QString name);

        private:*/
            Server();
            Server* singleton;
        };
    }
}

#endif // SERVER_H
