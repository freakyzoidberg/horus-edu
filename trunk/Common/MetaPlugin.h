#ifndef METAPLUGIN_H
#define METAPLUGIN_H

class MetaPlugin
{
public:
    virtual QList<Plugin*> getPluginList() = 0;

    enum PluginsType { HORUS_SERVER_PLUGIN, HORUS_CLIENT_PLUGIN };
    //! automaticaly return the type of this contained Plugins
#ifdef HORUS_CLIENT
    inline PluginsType pluginsType() { return HORUS_CLIENT_PLUGIN }
#else
#ifdef HORUS_SERVER
    inline PluginsType pluginsType() { return HORUS_SERVER_PLUGIN }
#else
#error "You must define HORUS_CLIENT or HORUS_SERVER in your project."
#endif
};

#endif // METAPLUGIN_H
