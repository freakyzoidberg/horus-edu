#ifndef MODULE_H
#define MODULE_H

#include <QString>

namespace Horus
{
    namespace Server
    {
        class Module
        {
        public:
            //virtual Module();
            const QString                 name;
/*
            virtual const std::list<Module&>  initAfterModules(const std::list<Module>& mods);

            virtual void                      onClientConect(Client& cli);
            virtual void                      onRecvClientData(Client& cli, void* data);
            */
        };
    } //[[1 asfdasiwef
}

#endif // MODULE_H
