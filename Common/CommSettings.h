#ifndef COMMCONFIG_H
#define COMMCONFIG_H

#include <QVariant>

#include "CommPacket.h"

//! Communication packet to GET/SET every users settings and system settings
class CommSettings : public CommPacket
{
public:
    /*!
     * UNDEFINED is used when the type is not set yet, and for invalid value
     * __LAST__ is usde to know if a value is valid. a valid value is always inferior to __LAST__. __LAST__ is never used as a value
     */
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
     *
     * __LAST_SCOPE__ is usde to know if a value is valid. a valid value is always inferior to __LAST_SCOPE__. __LAST_SCOPE__ is never used as a value
     */
    enum Scope  { CLIENT_USER_SCOPE, CLIENT_SYSTEM_SCOPE,
                  SERVER_USER_SCOPE, SERVER_SYSTEM_SCOPE,
                  __LAST_SCOPE__ };

    CommSettings();
    CommSettings(QByteArray& packet);
    const QByteArray    getPacket() const;

    //! method GET or SET settings
    Method              method;
    //! User or System config on the Client or Server side
    Scope               scope;
    //! plugin name (empty for no plugin)
    QByteArray          plugin;

    //! get all the settings in the binary format
    const QByteArray&   getBinarySettings() const;
    //! set all the settings in the binary format
    void                setBinarySettings(const QByteArray&);

    //! get all the settings in the QVariant format
    const QVariant      getVariantSettings() const;
    //! set all the settings in the QVariant format
    void                setVariantSettings(const QVariant&);

private:
    //! the settings in binary format
    QByteArray          settings;
    void                read(QByteArray&);
    void                write(QByteArray&) const;
};

QDebug operator<<(QDebug, const CommSettings&);

#endif // COMMCONFIG_H
