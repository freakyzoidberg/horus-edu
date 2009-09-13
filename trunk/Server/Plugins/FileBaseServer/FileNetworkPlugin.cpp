#include "FileNetworkPlugin.h"
#include "../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.h"
#include "FileTransfert.h"
#include "../../../Common/PluginManager.h"

void FileNetworkPlugin::receivePacket(UserData* user, const PluginPacket packet)
{
    if (packet.request != "askForConnexion")
        return;
    QVariantHash data = packet.data.toHash();
    FileTransfert* transfert = new FileTransfert(_dataPlugin->pluginManager->findPlugin<FileDataBasePlugin*>()->getFile(data["file"].toUInt()));

    data["key"] = transfert->key();
    emit sendPacket(user, PluginPacket(packet.sourcePlugin, "connexionAuthorized", data));
}
