#ifndef EDITPDF_H
#define EDITPDF_H

#include <QStringList>
#include <QWidget>

#include "editPDF_global.h"

class EDITPDFSHARED_EXPORT EditPDF
{
    public:
        EditPDF();
        QWidget *getTocInWidget();

    private:
        QStringList     pluginsRequired;

};

#endif // EDITPDF_H
