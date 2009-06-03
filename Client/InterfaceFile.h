#ifndef INTERFACEFILE_H
#define INTERFACEFILE_H

#include <QString>

#include "IFile.h"

//! "Implementation" of the interface IFile
/*!
  Must be modified, this is just small code just to make
  plugin using that compile.
*/

class InterfaceFile : public IFile
{
    public:
        InterfaceFile();
        /*!
          retrieve a file using its name
          \param name the name of the file
        */
        bool   needFile(const QString & fileName);
        /*!
          retrieve a file using its name
          \param id the id of the file
        */
        bool   needFile(int id);

        int    getFileIdByName(const QString & fileName);
        QString getNameById(int fileId);
};

#endif // INTERFACEFILE_H
