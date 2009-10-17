#ifndef EDITORPDF_H
#define EDITORPDF_H

#include <QLabel>
#include <QMouseEvent>
#include <QRubberBand>
# include "../LessonManager/ILessonDocument.h"

class EditorPdf : public QLabel
{
public:
                EditorPdf(QWidget *parent, ILessonDocument *);
    void        mousePressEvent(QMouseEvent *event);
    void        mouseMoveEvent(QMouseEvent *event);
    void        mouseReleaseEvent(QMouseEvent *event);

private:
    QRubberBand *rubberBand;
    QPoint      origin;
    ILessonDocument *doc;
};

#endif // EDITORPDF_H
