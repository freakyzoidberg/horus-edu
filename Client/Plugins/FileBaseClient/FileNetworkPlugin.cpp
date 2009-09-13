#include "FileNetworkPlugin.h"
#include "../../../Common/DataImplementations/FileDataBase/FileBase.h"
#include "../../../Common/DataImplementations/FileDataBase/FileDataBase.h"
#include "../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.h"

void FileNetworkPlugin::receivePacket(const PluginPacket packet)
{
    if (packet.request != "connexionAuthorized")
        return;

    QVariantHash data = packet.data.toHash();
    FileDataBase* file = ((FileDataBase*)(_dataPlugin->getFile( data["file"].toUInt() )));
    ((FileBase*)(file->device()))->connexionAuthorized( data["key"].toByteArray());
}

void FileNetworkPlugin::askForConnexion(FileData* file, QIODevice::OpenMode mode)
{
    QVariantHash data;
    data["mode"] = (quint32)mode;
    data["file"] = file->id();
    data["from"] = 0;
    emit sendPacket(PluginPacket("File Network Plugin", "askForConnexion", data));
}
