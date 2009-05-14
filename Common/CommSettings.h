#ifndef COMMCONFIG_H
#define COMMCONFIG_H

#include <QHash>
#include <QVariant>

#include "CommPacket.h"

class CommSettings : public CommPacket
{
public:
    enum Method { UNDEFINED,
                  GET, SET, //Client -> Server
                  VALUE, PERMISSION_DENIED, // Server -> Client
                  __LAST__ };
    //! type of configuration
    /*!
     * For the Client:
     *  CLIENT_USER_SCOPE: per user settings. only the owner can read and edit this settings
     *  CLIENT_SYSTEM_SCOPE: global settings. only an admin can edit this value but everybody can read it
     * For The Server:
     *  SERVER_USER_SCOPE: per user settings. only the owner can read and edit this settings
     *  SERVER_SYSTEM_SCOPE: global settings. only an admin can read and edit this settings
     */
    enum Scope  { CLIENT_USER_SCOPE, CLIENT_SYSTEM_SCOPE,
                  SERVER_USER_SCOPE, SERVER_SYSTEM_SCOPE,
                  __LAST_SCOPE__ };

    CommSettings();
    CommSettings(QByteArray&);
    const QByteArray    getPacket();

    //! method GET or SET settings
    Method              method;
    //! User or System config on the Client or Server side
    Scope               scope;
    //! module name (empty for no module)
    QByteArray          module;

    //! get all the settings in the binary format
    QByteArray          getBinarySettings(void);
    //! set all the settings in the binary format
    void                setBinarySettings(const QByteArray&);

    //! get all the settings in the QVariant format
    QVariant            getVariantSettings(void);
    //! get all the settings in the QVariant format
    void                setVariantSettings(const QVariant&);

private:
    //! the settings in binary format
    QByteArray          settings;
    void                read(QByteArray&);
    void                write(QByteArray&);
};

QDebug operator<<(QDebug, CommSettings&);

#endif // COMMCONFIG_H
