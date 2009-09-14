#include "FileNetworkPlugin.h"
#include "../../../Common/DataImplementations/FileDataBase/FileDataBase.h"
#include "../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.h"

void FileNetworkPlugin::receivePacket(const PluginPacket packet)
{
    if (packet.request != "downloadAuthorized" && packet.request != "uploadAuthorized")
        return;

    QVariantHash data = packet.data.toHash();
    FileDataBase* file = ((FileDataBase*)(_dataPlugin->getFile( data["file"].toUInt() )));

    if (packet.request == "downloadAuthorized")
        ((FileDataBase*)(file))->downloadAuthorized( data["key"].toByteArray());
    else
        ((FileDataBase*)(file))->uploadAuthorized( data["key"].toByteArray());
}

void FileNetworkPlugin::askForDownload(FileData* file)
{
    emit sendPacket(PluginPacket("File Network Plugin", "askForDownload", file->id()));
}

void FileNetworkPlugin::askForUpload(FileData* file)
{
    emit sendPacket(PluginPacket("File Network Plugin", "askForUpload", file->id()));
}
