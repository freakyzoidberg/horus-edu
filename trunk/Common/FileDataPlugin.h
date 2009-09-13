#ifndef FILEDATAPLUGIN_H
#define FILEDATAPLUGIN_H

#include <QHash>
#include "DataPlugin.h"

class Data;
class FileData;
class FileDataPlugin : public DataPlugin
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerDataPlugin)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientDataPlugin)
#endif

public:
    inline const QString getDataType() const { return "File"; }
    virtual FileData*    getFile(quint32 fileId) = 0;
};

#ifdef HORUS_SERVER
typedef FileDataPlugin ServerFileDataPlugin;
Q_DECLARE_INTERFACE(ServerFileDataPlugin, "net.horus.ServerFileDataPlugin/1.0");
#endif
#ifdef HORUS_CLIENT
typedef FileDataPlugin ClientFileDataPlugin;
Q_DECLARE_INTERFACE(ClientFileDataPlugin, "net.horus.ClientFileDataPlugin/1.0");
#endif

#endif // FILEDATAPLUGIN_H
