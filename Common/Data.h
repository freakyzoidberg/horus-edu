#ifndef DATA_H
#define DATA_H

#ifdef HORUS_SERVER
  #include <QtSql>
#else
#ifdef HORUS_CLIENT
  #include <QColor>
#else
  #error "You must define HORUS_CLIENT or HORUS_SERVER in your project."
#endif
#endif

#include <QMutex>
#include <QDataStream>
#include <QString>
#include <QDebug>
#include <QVariant>
#include <QDateTime>

#include "DataPlugin.h"
#include "DataManager.h"
#include "PluginManager.h"

class UserData;
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
    virtual inline void     dataToStream(QDataStream& s) { s << _lastChange; }
    //! Have to read his data from the stream.
    /*! Called to:
     *  - Transfert this data between client and server.
     *  - Read from a local cache file.
     */
    virtual inline void     dataFromStream(QDataStream& s) { s >> _lastChange; }

	//! Function to create the value of the data
	inline void             create() { setStatus(CREATING); }

	//! Function to save the value of the data
    inline void             save() { setStatus(SAVING); }

    //! Function to delete the value of the data
    inline void             remove() { setStatus(DELETING); }

    //! Return the current status of this data.
    inline quint8           status() const { return (quint8)_status; }
    //! Change the current status and tell the coresponding plugin the data just changed.
	inline void             setStatus(quint8 status) { _plugin->dataManager->dataStatusChange(this, status); }

    inline const QDateTime lastChange() { return _lastChange; }

#ifdef HORUS_CLIENT
	inline bool canAccess() { return canAccess(_plugin->pluginManager->currentUser()); }
	inline bool canChange() { return canChange(_plugin->pluginManager->currentUser()); }
#endif
	virtual inline bool canChange(UserData*) { return true; }
	virtual inline bool canAccess(UserData*) { return true; }

signals:
    //! Signal emmited when the data is updated.
    void                    updated();
    //! Signal emmited when an error append on this data
    void                    dataError(quint8 error);

public:
    //! Usefull for debuging. Not mandatory but important.
    virtual inline QDebug   operator<<(QDebug debug) const { return debug << getDataType(); }
#ifdef HORUS_CLIENT
    virtual inline QVariant data(int, int role = Qt::DisplayRole) const
    {
        if (role == Qt::BackgroundColorRole)
        {
            if (status() == UPTODATE)
                return QColor(210, 255, 210);//green : uptodate
            if (status() == SAVING || status() == CREATING)
                return QColor(210, 210, 255);//blue : saving & creating
            if (status() == DELETING)
                return QColor(255, 210, 210);//red : deleting

            return QColor(220, 220, 220);//gray : cached, updating, ...
        }
        return QVariant();
    }

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
    QDateTime               _lastChange;

    QMutex                  *lock;
};

inline QDebug operator<<(QDebug debug, const Data& data) { return data << debug; }
inline QDebug operator<<(QDebug debug, const Data* data) { if (data) return (*data) << debug; else return debug << "null"; }

#ifdef HORUS_SERVER
typedef Data ServerData;
Q_DECLARE_INTERFACE(ServerData, "net.horus.ServerData/1.0");
#endif
#ifdef HORUS_CLIENT
typedef Data ClientData;
Q_DECLARE_INTERFACE(ClientData, "net.horus.ClientData/1.0");
#endif

#endif // DATA_H

