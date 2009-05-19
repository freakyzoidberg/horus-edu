#ifndef IMETADATA_H
#define IMETADATA_H

#include <QString>
#include <QFile>

//! Access to the medata of a PDF files
/*!
    This class contains method allowing to read the medata
    used to customize the PDF file.
*/
class   IMetaData
{
    public:
        virtual const QString   getMetaFileName() const = 0;
        virtual const QFile     *getMetaFile() const = 0;

        virtual void            openMetaFile() = 0;
        virtual void            closeMetaFile() = 0;
        /*
          methods to get the data, probably using something like QTXML module
         */
};

#endif // IMETADATA_H
