#ifndef EDITPDF_H
#define EDITPDF_H

#include <QStringList>
#include <QWidget>
#include <QObject>
#include <QDomNode>

#include "TreeWidgetItem.h"

#include "editPDF_global.h"

class EDITPDFSHARED_EXPORT EditPDF : QObject
{
    public:
        EditPDF();
        QWidget *getTocInWidget();
        void    buildTocWidget(QDomNode *, TreeWidgetItem *);

    private:
        QStringList     pluginsRequired;
        QTreeWidget     *tree;
};

#endif // EDITPDF_H
