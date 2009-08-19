#ifndef FILEDATA_H
#define FILEDATA_H

#include "Data.h"
#include "FileDataPlugin.h"


class FileData : public Data
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerData)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientData)
#endif

protected:
	inline FileData(quint32 fileId, FileDataPlugin* plugin) : Data(plugin) {} //je sais git, c pour que ca compile
    inline ~FileData() {}
public:
};

#ifdef HORUS_SERVER
typedef FileData ServerFileData;
Q_DECLARE_INTERFACE(ServerFileData, "net.horus.ServerFileData/1.0");
#endif
#ifdef HORUS_CLIENT
typedef FileData ClientFileData;
Q_DECLARE_INTERFACE(ClientFileData, "net.horus.ClientFileData/1.0");
#endif

#endif // FILEDATA_H
