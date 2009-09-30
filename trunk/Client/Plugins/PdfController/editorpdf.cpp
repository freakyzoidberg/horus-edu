#include "editorpdf.h"

#include <QRubberBand>
#include <QPoint>

EditorPdf::EditorPdf(QWidget *parent) : QLabel(parent)
{
    this->lower();
}

void EditorPdf::mousePressEvent(QMouseEvent *event)
 {
     int    x = event->pos().x();
     int    y = event->pos().y();
     QPoint origin(x, y);
     //  if (!rubberBand)
    rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    rubberBand->setGeometry(QRect(origin, QSize()));
    rubberBand->show();
 }

 void EditorPdf::mouseMoveEvent(QMouseEvent *event)
 {
     rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
 }

 void EditorPdf::mouseReleaseEvent(QMouseEvent *event)
 {
     rubberBand->hide();
 }

