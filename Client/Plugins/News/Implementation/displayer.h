#ifndef DISPLAYER_H
#define DISPLAYER_H
#include <QObject>

class DisplayerPrivate;
class QWidget;
class Displayer: public QObject
{
Q_OBJECT
public:
    Displayer(QObject *parent = 0);
    ~Displayer();

    void activateOn(QWidget *widget);
    void deactivateFrom(QWidget *widget);
    bool eventFilter(QObject *object, QEvent *event);

protected:
    void timerEvent(QTimerEvent *event);

private:
    DisplayerPrivate *d;
};


#endif // DISPLAYER_H
