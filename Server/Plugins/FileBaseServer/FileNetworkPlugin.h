#ifndef FILENETWORKPLUGIN_H
#define FILENETWORKPLUGIN_H

#include "../../NetworkPlugin.h"

class FileDataBasePlugin;
class FileNetworkPlugin : public NetworkPlugin
{
  Q_OBJECT
  Q_INTERFACES(NetworkPluginServer)

// Plugin Interface
public:
    inline const QString pluginName() const { return "File Network Plugin"; }
    inline const QString pluginVersion() const { return "0.1"; }


// NetworkPlugin Interface
public slots:
    void receivePacket(UserData* user, const PluginPacket);


public:
    inline FileNetworkPlugin(FileDataBasePlugin* dataPlugin) { _dataPlugin = dataPlugin; }
private:
    FileDataBasePlugin* _dataPlugin;
};

#endif // FILENETWORKPLUGIN_H
