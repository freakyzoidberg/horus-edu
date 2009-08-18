#ifndef DATAMANAGERSERVER_H
#define DATAMANAGERSERVER_H

#include "../Common/DataManager.h"

class DataPlugin;
class DataManagerServer : public DataManager
{
public:
     inline DataManagerServer(DataPlugin* _plugin) : DataManager(_plugin) { plugin=_plugin; }

    //! Called by the data when its status change.
    /*!
     *  Have differents implementation on the Client and the Server.
     *  Can be overloaded if:
     *  - More status are supported (ex: a file can be [up/down]loading)
     *  - To check permitions (also on the client side but can be less restrictive)
     */
    void dataStatusChange(Data* data, quint8 newStatus) const;
    void receiveData(UserData* user, const QByteArray& packet) const;
    void sendData(UserData* user, Data* data) const;
    void sendData(UserData* user, const QByteArray& packet) const;

private:
    DataPlugin* plugin;
};

#endif // DATAMANAGERSERVER_H
