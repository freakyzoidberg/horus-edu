#ifndef LABEL_H
#define LABEL_H

#include <QDebug>

#include <QLabel>
#include <QMouseEvent>

class Label : public QLabel
{
Q_OBJECT

public:
    Label(QString message, QWidget *parent);
    void    mouseReleaseEvent(QMouseEvent *event);

signals:
    void    clicked();
};

#endif // LABEL_H
