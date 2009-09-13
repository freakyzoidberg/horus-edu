#ifndef FILEDATA_H
#define FILEDATA_H

#include "Data.h"
#include "FileDataPlugin.h"
#include <QFile>
class UserData;
class TreeData;

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
    inline FileData(FileDataPlugin* plugin) : Data(plugin) { }
    inline ~FileData() {}

public:
    virtual quint32     id() const = 0;

    virtual QString     name() const = 0;
    virtual void        setName(const QString name) = 0;

    virtual UserData*   owner() const = 0;

    virtual TreeData*   node() const = 0;
    virtual void        moveTo(TreeData* node) = 0;

    virtual QString     mimeType() const = 0;

    virtual QFile*      localFile() const = 0;

#ifdef HORUS_CLIENT
    virtual void        synchronize() = 0;
#endif

signals:
    void                synchronized();
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
