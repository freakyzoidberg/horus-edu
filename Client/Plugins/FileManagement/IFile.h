#ifndef IFILE_H
#define IFILE_H

#include <QIODevice>

#include "FileInfo.h"

class IFile : public QIODevice
{
  Q_OBJECT
public:
    //! return the progress value (for a down/up-load)
    virtual int   getProgress() const = 0;
    //! return the informations of the file (size,owner,...)
    virtual const FileInfo& getInfo() const = 0;
    //! return true if the localfile is the same as the server
    virtual bool isSynchronized() const = 0;
    //! open the transfert connexion if needed and the local file
    virtual bool open(OpenMode mode) = 0;
    virtual bool isOopen() const = 0;
    //! close after finishing the curent synchronization
    virtual void close() = 0;
    //! return the localFileName
    virtual const QString getLocalFileName() const = 0;
    //! set the filename
    virtual void setFileName(const QString&) = 0;

signals:
    //! emitted an error append
    //void error(int code, QString message);
    //! emitted when the fileInformation change
    void fileInfoUpdated();
    //! emitted when the localfile is the same as the server
    void fileSynchronized();
    ////! emitted when a connexion to the server is opened (maybe useless)
    //void connexionOpened();
    //! emitted when the progress value change (for a down/upload)
    void progressChange(int percent);

protected:
    virtual ~IFile() {}
};

#endif // IFILE_H
