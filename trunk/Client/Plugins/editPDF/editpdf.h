#ifndef EDITPDF_H
#define EDITPDF_H

#include <QStringList>
#include <QWidget>
#include <QDomNode>
#include <QTreeWidgetItem>
#include "editPDF_global.h"

class EDITPDFSHARED_EXPORT EditPDF
{
    public:
        EditPDF();
        QWidget *getTocInWidget(QDomNode *, QTreeWidgetItem *);

    private:
        QStringList     pluginsRequired;

};

#endif // EDITPDF_H
