#include "FileNetworkPlugin.h"
#include "FileTransfertServer.h"
#include "../../../Common/FileData.h"
#include "../../../Common/PluginManager.h"
#include "../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.h"

void FileNetworkPlugin::receivePacket(UserData* user, const PluginPacket packet)
{
    if (packet.request != "askForDownload" && packet.request != "askForUpload")
        return;

    FileData* file = _dataPlugin->pluginManager->findPlugin<FileDataBasePlugin*>()->getFile( packet.data.toUInt() );
    QVariantHash data;
    data["file"] = file->id();

    FileTransfert::TransfertType type;
    QString response;
    if (packet.request == "askForDownload")
    {
        type = FileTransfert::DOWNLOAD;
        response = "downloadAuthorized";
    }
    else
    {
        type = FileTransfert::UPLOAD;
        response = "uploadAuthorized";
    }

	data["key"] = (new FileTransfertServer(file, type))->key();

    emit sendPacket(user, PluginPacket(packet.sourcePlugin, response, data));
}
