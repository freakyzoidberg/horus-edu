#ifndef EDITORPDF_H
#define EDITORPDF_H

#include <QLabel>
#include <QMouseEvent>
#include <QRubberBand>

class EditorPdf : public QLabel
{
public:
                EditorPdf(QWidget *parent);
    void        mousePressEvent(QMouseEvent *event);
    void        mouseMoveEvent(QMouseEvent *event);
    void        mouseReleaseEvent(QMouseEvent *event);

private:
    QRubberBand *rubberBand;
    QPoint      origin;
};

#endif // EDITORPDF_H
