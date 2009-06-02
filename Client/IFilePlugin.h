#ifndef IFILEPLUGIN_H
#define IFILEPLUGIN_H

#include <QIODevice>

#include "IFile.h"

class   IFilePlugin
{
    public:
    /*!
       Access to files stored on the server. Each plugins
       implementing this interface will be able to retrieve
       files they need if their are not in local.
    */
    IFile     *file;
};

#endif // IFILEPLUGIN_H
