#ifndef EDITPDF_H
#define EDITPDF_H

#include <QStringList>

#include "editPDF_global.h"

class EDITPDFSHARED_EXPORT EditPDF
{
    public:
        EditPDF();

    private:
        QStringList     pluginsRequired;

};

#endif // EDITPDF_H
