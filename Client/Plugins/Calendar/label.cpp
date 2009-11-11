#include <QMouseEvent>

#include "label.h"

Label::Label(QString message, QWidget *parent) : QLabel(message, parent)
{
    this->setTextInteractionFlags(Qt::TextBrowserInteraction);
    this->setOpenExternalLinks(false);
}

void    Label::mouseReleaseEvent(QMouseEvent *event)
{
    emit clicked();
}

