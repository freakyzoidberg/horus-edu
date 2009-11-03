#include <QPushButton>

#include "addeventwidget.h"

#include <QDebug>

AddEventWidget::AddEventWidget()
{
    _cancel = new QPushButton(tr("Cancel"), this);
    _save = new QPushButton(tr("Save"), this);

    _save->setVisible(false);
    _cancel->setVisible(false);
}
