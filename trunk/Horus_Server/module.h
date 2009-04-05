#ifndef MODULE_H
#define MODULE_H

#include <QString>

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

#endif // MODULE_H
