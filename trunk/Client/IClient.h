#ifndef ICLIENT_H
#define ICLIENT_H

#include <QByteArray>

class IClientPlugin;

//! Interface given to each client plugin to communicate with the client
/*!
 *  This interface implements network relative functions which must be in a specific network interface
 */
class IClient
{
public:

    //! A function for accessing plugins from other plugins
    /*!
     *  This function return the instance of plugin from his name.
     *  A plugin can only be instancieted once, so each name is unique.
     *  It is destinated for plugins willing to contacts other plugins
     *  \param name the name of the desired plugin
     *  \return a pointer to the instance of the desired plugin or NULL if not found
     */
    virtual IClientPlugin   *getPlugin(const QByteArray name) const = 0;
};

#endif // ICLIENT_H
