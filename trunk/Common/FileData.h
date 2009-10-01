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
	virtual void        setMimeType(const QString name) = 0;

    virtual QFile*      file() const = 0;

#ifdef HORUS_CLIENT
    //! return the progress value (for a down/up-load)
    virtual int     progress() const = 0;
    //! download the file from the server.
    virtual void  download() = 0;
    //! return true if the file is downloaded in local
    virtual bool    isDownloaded() const = 0;
    //! upload the file to the server.
    virtual void  upload() = 0;

signals:
    //! emitted when the localfile just finish downloading
    void downloaded();
    //! emitted when the localfile just finish uploading
    void uploaded();
    //! emitted when the progress value change (for a down/upload)
    void progressChange(int percent);
#endif
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
