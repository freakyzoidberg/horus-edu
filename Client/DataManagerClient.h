#ifndef DATAMANAGERCLIENT_H
#define DATAMANAGERCLIENT_H

#include "../Common/DataManager.h"

class DataPlugin;
class DataManagerClient : public DataManager
{
  Q_OBJECT
public:
    inline DataManagerClient(DataPlugin* parent) : DataManager(parent) { plugin = parent; }

    //! Called by the data when its status change.
    /*!
     *  Have differents implementation on the Client and the Server.
     *  Can be overloaded if:
     *  - More status are supported (ex: a file can be [up/down]loading)
     *  - To check permitions (also on the client side but can be less restrictive)
     */
    void dataStatusChange(Data* data, quint8 newStatus) const;
    void sendData(UserData* user, Data* data) const;
    void sendData(UserData* user, const QByteArray& packet) const;

public slots:
    void receiveData(UserData* user, const QByteArray& packet) const;

private:
    DataPlugin* plugin;
};

#endif // DATAMANAGERCLIENT_H
