#ifndef PLUGIN_H
#define PLUGIN_H

#include <QtCore/qglobal.h>
#include <QtPlugin>
#include <QObject>
#include <QStringList>
#include <QDebug>

class PluginManager;
class Plugin : virtual public QObject
{
  Q_OBJECT
public:

    //! Return the name of the plugin.
    /*!
     *  This method provide the name of the plugin.
     *  Each plugin must have an unique name.
     *  \return the name of the plugin
     */
    virtual const QString   pluginName()    const = 0;
    //! Return the version of the plugin.
    /*!
     *  This function provide the version of the plugin.
     *  \return the version of the plugin
     */
    virtual const QString   pluginVersion() const = 0;

    //! Return true if the module can be loaded (true by default).
    virtual inline bool     canLoad()       const { return true; }
    //! Return true if the module is loaded.
    virtual inline bool     isLoaded()      const { return loaded; }
    //! Called to start the plugin, after canLoad and if isLoaded() == false.
    virtual inline void     load()                { loaded = true; qDebug() << "Plugin::load()" << pluginName();}
    //! Called to stop the plugin and free memory.
    virtual inline void     unload()              { loaded = false; }

    //! The object to access every other plugins and the current user on the client.
    PluginManager*          pluginManager;

protected:
    inline                  Plugin()              { loaded = false; }
private:
    bool                    loaded;
};

Q_DECLARE_INTERFACE(Plugin, "net.horus.Plugin/1.0");

#endif // PLUGIN_H
