#ifndef FILEBASE_H
#define FILEBASE_H

#include <QFile>
#include <QSslSocket>

#include "../../../Common/File.h"

class FileDataBase;
class FileDataBasePlugin;
class FileBase : public File
{
  Q_OBJECT

  friend class FileBasePlugin;
  friend class FileDataBase;

public:
    //! return the progress value (for a down/up-load)
    int   progress() const;
    //! return true if the localfile is the same as the server
    inline bool  isSynchronized() const { return _synchronized; }
    //! open the transfert connexion if needed and the local file
    bool  open(OpenMode mode);
    //! true if the device is open
    bool  isOopen() const;
    //! close after finishing the curent synchronization
    void  close();
    //! download the file from the server or upload it.
    void  synchronize();
    //! called by FileManager, open the connexion
    void        connexionAuthorized(const QByteArray& key);

protected:
    qint64 writeData(const char* data, qint64 maxSize);
    qint64 readData(char* data, qint64 maxSize);

private:
    //! private constructor, to keep clear of multiple instance of the same file, only File can new
    FileBase(FileDataBase* fileData, FileDataBasePlugin* plugin);
    //! private destructor, to block delete from outside, only File can delete
    ~FileBase();

    //! true if the localfile is the same as the server file
    bool        _synchronized;

    bool        _connecting;

    //! the socket to the server if needed
    QSslSocket  _socket;
    //! keep the socket position
    qint64      _socketPos;
    //! the localfile
    QFile       _file;

    FileDataBasePlugin* _plugin;

private slots:
    void fileBytesWritten(qint64);
    void connexionReadyRead();
    void connexionBytesWritten(qint64);
    void connexionDisconnected();
};

#endif // FILEBASE_H
