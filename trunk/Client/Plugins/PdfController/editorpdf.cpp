#include "editorpdf.h"

#include <QRubberBand>
#include <QPoint>

EditorPdf::EditorPdf(QWidget *parent) : QLabel(parent)
{
}

void EditorPdf::mousePressEvent(QMouseEvent *event)
 {
     QPoint origin = event->pos();
     if (!rubberBand)
         rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
   //  rubberBand->setGeometry(QRect(origin, QSize()));
   //  rubberBand->show();
 }

 void EditorPdf::mouseMoveEvent(QMouseEvent *event)
 {
     //rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
 }

 void EditorPdf::mouseReleaseEvent(QMouseEvent *event)
 {
   //rubberBand->hide();
 }

