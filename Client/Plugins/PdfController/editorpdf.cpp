#include "editorpdf.h"

#include <QRubberBand>
#include <QPoint>

EditorPdf::EditorPdf(QWidget *parent, ILessonDocument *doc) : QLabel(parent)
{
    this->doc = doc;
    this->lower();
    rubberBand = NULL;
}

void EditorPdf::mousePressEvent(QMouseEvent *event)
 {
    int    x = event->pos().x();
    int    y = event->pos().x();

    qDebug() << "x=" << x << "   y=" << y;

    QPoint origin(x, y);

    qDebug() << "origin:" << origin;

    if (!rubberBand)
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
    delete rubberBand;
    rubberBand = NULL;
 }

