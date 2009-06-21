#ifndef METAPLUGIN_H
#define METAPLUGIN_H

#include <QtCore/qglobal.h>
#include <QObject>
#include <QtPlugin>
#include <QList>

#include "Plugin.h"

class MetaPlugin : public QObject
{
  Q_OBJECT
public:
    QList<Plugin*> pluginList;

    enum PluginsType { HORUS_SERVER_PLUGIN, HORUS_CLIENT_PLUGIN };
    //! automaticaly return the type of this contained Plugins
    inline PluginsType pluginsType() {
#ifdef HORUS_CLIENT
        return HORUS_CLIENT_PLUGIN;
#else
#ifdef HORUS_SERVER
        return HORUS_SERVER_PLUGIN;
#else
  #error "You must define HORUS_CLIENT or HORUS_SERVER in your project."
#endif
#endif
    }
};

Q_DECLARE_INTERFACE(MetaPlugin, "net.horus.MetaPlugin/1.0");

#endif // METAPLUGIN_H
