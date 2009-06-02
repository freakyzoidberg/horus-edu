#ifndef TESTCOMM_H
#define TESTCOMM_H

#include <QtSql>

#include "../../../Common/Defines.h"
#include "../IServer.h"
#include "../IServerPlugin.h"

//! a Server Plugin to test the communication between a Client Plugin and a Server Plugin
class UserManagment : public IServerPlugin
{
  Q_OBJECT
  Q_INTERFACES(IServerPlugin)

  typedef void (UserManagment::*requestFunction)(quint32 userId, const QVariantHash& request,QVariantHash& response);

public:
    UserManagment();

    inline const QByteArray  name()    const { return "UserManagment"; }
    inline quint8            version() const { return 0; }

    void recvPacket(quint32 userId, const PluginPacket&);

private:
    //! functions for each request
    /*! called by recvPacket */
    QHash<QByteArray,requestFunction> requestFunctions;

    //! if request is not found
    void unknownRequest   (quint32 userId, const QVariantHash& request,QVariantHash& response);

    //! the connected user can change his own password and an admin can change every passwords
    void changePassword   (quint32 userId, const QVariantHash& request,QVariantHash& response);
    //! list all users
    void listUsers        (quint32 userId, const QVariantHash& request,QVariantHash& response);
    //! get informations about a user
    void getUserInfo      (quint32 userId, const QVariantHash& request,QVariantHash& response);
    //! edit informations about a user
    void setUserInfo      (quint32 userId, const QVariantHash& request,QVariantHash& response);
    //! create a new user
    void createNewUser    (quint32 userId, const QVariantHash& request,QVariantHash& response);
    //! disable/enable a user
    void disableUser      (quint32 userId, const QVariantHash& request,QVariantHash& response);
};

#endif // TESTCOMM_H
