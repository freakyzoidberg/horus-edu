#ifndef DATA_H
#define DATA_H

#ifdef HORUS_SERVER
  #include <QtSql>
#else
#ifndef HORUS_CLIENT
  #error "You must define HORUS_CLIENT or HORUS_SERVER in your project."
#endif
#endif

#include <QMutex>
#include <QDataStream>
#include <QString>
#include <QDebug>

#include "DataPlugin.h"

class UserData;
class PluginManager;
class Data : public QObject
{
  Q_OBJECT
#ifdef HORUS_SERVER
  friend class DataManagerServer;
#endif
#ifdef HORUS_CLIENT
  friend class DataManagerClient;
#endif

public:
    //                          // key|value| other
    enum DataStatus { EMPTY,    //  - |  -  |
                      CACHED,   //  X |  X  |
                    // CLIENT -> SERVER
                      UPDATING, //  X |  -  |
                      SAVING,   //  X |  X  | old data
                      CREATING, //  X |  X  |
                      DELETING, //  X |  -  |
                    // SERVER -> CLIENT
                      UPTODATE, //  X |  X  |
                      SAVED,    //  X |  -  |
                      CREATED,  //  X |  -  | new key
                      DELETED}; //  X |  -  |
    //              error!=NONE //  X |  -  |
    enum Error { NONE=0, PERMITION_DENIED=1, NOT_FOUND=2, DATABASE_ERROR=3, DATA_ALREADY_CHANGED=4 };

    inline quint8           error() const { return _error; }
    inline void             setError(quint8 e) { _error=e; if (_error) emit dataError(_error); }

    inline const QString    getDataType() const { return _plugin->getDataType(); }


    //! Have to write his key into the stream to be able to identify this data with the server and the cache.
    virtual void            keyToStream(QDataStream& s) = 0;
    //! Have to write his data into the stream.
    /*! Called to:
     *  - Transfert this data between client and server.
     *  - Write to a local cache file.
     *  - Compare two data.
     */
    virtual void            dataToStream(QDataStream& s) = 0;
    //! Have to read his data from the stream.
    /*! Called to:
     *  - Transfert this data between client and server.
     *  - Read from a local cache file.
     */
    virtual void            dataFromStream(QDataStream& s) = 0;

    //! Function to call before editing a data.
    /*! This function make a copy of the data.
     *  after, when the function setStatus( SAVE ) is called
     *  the old and the new value is send
     *  if the data already change, server will know
     *  if permition denied, client still have the old value
     */
    inline void            preSaveData() { oldValue=""; QDataStream s(&oldValue, QIODevice::WriteOnly); dataToStream(s); }

    //! Return the current status of this data.
    inline quint8           status() const { return (quint8)_status; }
    //! Change the current status and tell the coresponding plugin the data just changed.
    inline void             setStatus(quint8 status) {
        _plugin->dataManager->dataStatusChange(this, status);
        if (_status == UPTODATE) emit updated();
    }

signals:
    //! Signal emmited when the data is updated.
    void                    updated();
    //! Signal emmited when an error append on this data
    void                    dataError(quint8 error);

public:
    //! Usefull for debuging. Not mandatory but important.
    virtual inline QDebug   operator<<(QDebug debug) const { return debug << getDataType(); }
#ifdef HORUS_CLIENT
    virtual QVariant        data(int column, int role = Qt::DisplayRole) const = 0;
    //! Function just set the UPDATING status if not already uptodate or updating
    inline void             update()
        { if (_status == EMPTY || _status == UPTODATE || _status == CACHED) setStatus(UPDATING); }
#endif
#ifdef HORUS_SERVER
    //! Fill the current data with a defined key from teh database.
    virtual void            fillFromDatabase  (QSqlQuery&) = 0;
    //! Create this data into the database, and update the key.
    virtual void            createIntoDatabase(QSqlQuery&) = 0;
    //! Save the current data into the database.
    virtual void            saveIntoDatabase  (QSqlQuery&) = 0;
    //! Delete the current data from the database.
    virtual void            deleteFromDatabase(QSqlQuery&) = 0;
#endif

protected:
    inline Data(DataPlugin* plugin) { _plugin=plugin; _status=EMPTY; _error=NONE; lock=new QMutex(QMutex::Recursive); }
    inline ~Data() { delete lock; }

    DataPlugin*             _plugin;
    quint8                  _status;
    quint8                  _error;

    QMutex                  *lock;

private:
    QByteArray              oldValue;
};

inline QDebug operator<<(QDebug debug, const Data& data) { return data << debug; }
inline QDebug operator<<(QDebug debug, const Data* data) { return (*data) << debug; }

#ifdef HORUS_SERVER
typedef Data ServerData;
Q_DECLARE_INTERFACE(ServerData, "net.horus.ServerData/1.0");
#endif
#ifdef HORUS_CLIENT
typedef Data ClientData;
Q_DECLARE_INTERFACE(ClientData, "net.horus.ClientData/1.0");
#endif

#endif // DATA_H
