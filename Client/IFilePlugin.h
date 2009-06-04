#ifndef IFILEPLUGIN_H
#define IFILEPLUGIN_H

#include <QIODevice>

#include "IFileManager.h"

class   IFilePlugin
{
    public:
    /*!
       Access to files stored on the server. Each plugins
       implementing this interface will be able to retrieve
       files they need if their are not in local.
    */
    IFileManager     *fileManager;
};

Q_DECLARE_INTERFACE(IFilePlugin, "net.horus.Client.FileInterface/1.0");

#endif // IFILEPLUGIN_H
