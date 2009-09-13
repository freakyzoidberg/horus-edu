#ifndef FILE_H
#define FILE_H

#include <QIODevice>
class FileData;

class File : public QIODevice
{
  Q_OBJECT
public:
    //! return the progress value (for a down/up-load)
    virtual int     progress() const = 0;
    //! return true if the localfile is the same as the server
    virtual bool    isSynchronized() const = 0;
    //! download the file from the server or upload it.
    virtual void    synchronize() = 0;
    //! return the associated FileData
    inline FileData* data() { return _fileData; }

signals:
    //! emitted when the localfile is the same as the server
    void synchronized();
    //! emitted when the progress value change (for a down/upload)
    void progressChange(int percent);

protected:
    inline File(FileData* fileData) { _fileData = fileData; }
    inline ~File() {}

private:
    FileData*   _fileData;
};

#endif // FILE_H
