#ifndef DATA_H
#define DATA_H

#include <QDataStream>

class IDataPlugin
{

public:
    virtual IData* getEmptyData() const = 0;
    //! called when a new data is received
    /*!
     *
     */
    virtual void incommingData(IData* data, ) = 0;
protected:
    DataManager dataManager;
};

class DataManager
{
public slots:
     statusChange(DataModel::DataStatus oldStatus);
};

class DataModel : public QObject
{

public:
    inline DataModel(DataManager* manager, DataStatus status)
            { connect(this, SIGNAL(statusChanged(DataStatus)), manager, SLOT(statusChange(DataStatus))); }

    virtual const char* getType() = 0;

    //! called to transfert this data with the server or write to a local cache file
    virtual void writeToStream(QDataStream& s) = 0;
    //! called to transfert this data with the server or read from a local cache file
    virtual void readFromStream(QDataStream& s) = 0;

#ifdef HORUS_CLIENT
public:
    void update();
signals:
    void updated();
#endif

  enum DataStatus { EMPTY, UPDATING, SAVING, CREATING, DELETING, CACHED, UPTODATE, CREATED, DELETED };
signals:
    //! the status of this data just changed
    void statusChanged(DataStatus oldStatus);
public:
    inline void        setStatus(DataStatus _status) { DataStatus old=status; status=_status; emit statusChanged(old); }
    inline DataStatus  getStatus() { return status; }
private:
    DataStatus status;
};

#endif // DATA_H
