#ifndef IFILE_H
#define IFILE_H

#include <QFile>

//!interface use to get file from the server.
class   IFile
{
    public:
        /*!
          retrieve a file using its name
          \param name the name of the file
        */
        virtual void   needFile(const QString & fileName) = 0;
        /*!
          retrieve a file using its name
          \param id the id of the file
        */
        virtual void   needFile(int id) = 0;
};

#endif // IFILE_H
