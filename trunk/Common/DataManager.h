#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QtPlugin>
#include "Defines.h"

class Data;
class UserData;
class DataManager
{
public:
    //! Called by the data when its status change.
    /*!
     *  Have differents implementation on the Client and the Server.
     *  Can be overloaded if:
     *  - More status are supported (ex: a file can be [up/down]loading)
     *  - To check permitions (also on the client side but can be less restrictive)
     */
    virtual void dataStatusChange(UserData* user, Data* data, quint8 newStatus) const = 0;

    virtual void receiveData(UserData* user, const QByteArray& data) const = 0;
    virtual void sendData(UserData* user, Data* data) const = 0;
};

#endif // DATAMANAGER_H
