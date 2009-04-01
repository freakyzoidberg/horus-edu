#ifndef MODULE_H
#define MODULE_H

namespace Horus
{
    namespace Server
    {
        class Module
        {
        public:
            virtual Module();
            const std::string                 name;

            virtual const std::list<Module&>  initAfterModules(const std::list<Module>& mods);

            virtual void                      onClientConect(Client& cli);
            virtual void                      onRecvClientData(Client& cli, void* data);
        };
    }
}

#endif // MODULE_H
