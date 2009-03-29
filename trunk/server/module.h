#ifndef MODULE_H
#define MODULE_H

namespace Horus
{
    namespace Server
    {
        class Module
        {
        public:
            Module();
            const std::string                 Name;

            virtual const std::list<Module&>  initAfterModules(const std::list<Module>& mods);

            virtual void                      onInit();
            virtual void                      onClientConect(Client& cli);
            virtual void                      onRecvClientData(Client& cli, void* data);
        };
    };
};

#endif // MODULE_H
