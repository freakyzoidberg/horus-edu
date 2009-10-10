#ifndef FILENETWORKPLUGIN_H
#define FILENETWORKPLUGIN_H

#include "../../NetworkPlugin.h"

class FileData;
class FileDataBasePlugin;
#include "FileTransfertClient.h"

class FileNetworkPlugin : public NetworkPlugin
{
  Q_OBJECT
  Q_INTERFACES(NetworkPluginClient)

// Plugin Interface
public:
    inline const QString    pluginName() const { return "File Network Plugin"; }
    inline const QString    pluginVersion() const { return "0.1"; }


// NetworkPlugin Interface
public slots:
    void                    receivePacket(const PluginPacket);


public:
    inline FileNetworkPlugin(FileDataBasePlugin* dataPlugin) { _dataPlugin = dataPlugin; }
	void                    askForTransfert(FileData* file, FileTransfert::TransfertType type);
private:
    FileDataBasePlugin* _dataPlugin;
};

#endif // FILENETWORKPLUGIN_H
