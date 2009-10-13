#include "displayer.h"
#include <QApplication>
#include <QPoint>
#include <QAbstractScrollArea>
#include <QScrollBar>
#include <QEvent>
#include <QMouseEvent>
#include <QHash>
#include <QBasicTimer>
#include <QWebView>
#include <QWebFrame>
#include <QDebug>


struct DisplayerData {
    typedef enum { Steady, Pressed, ManualScroll, AutoScroll, Stop } State;
    State state;
    QWidget *widget;
    QPoint pressPos;
    QPoint offset;
    QPoint dragPos;
    QPoint speed;
    QList<QEvent*> ignored;
};

class DisplayerPrivate
{
public:
    QHash<QWidget*, DisplayerData*> dispData;
    QBasicTimer ticker;
};

Displayer::Displayer(QObject *parent): QObject(parent)
{
    d = new DisplayerPrivate;
}

Displayer::~Displayer()
{
    delete d;
}


void Displayer::activateOn(QWidget *widget)
{
    QAbstractScrollArea *scrollArea = dynamic_cast<QAbstractScrollArea*>(widget);
    if (scrollArea) {
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        QWidget *viewport = scrollArea->viewport();

        viewport->installEventFilter(this);
        scrollArea->installEventFilter(this);

        d->dispData.remove(viewport);
        d->dispData[viewport] = new DisplayerData;
        d->dispData[viewport]->widget = widget;
        d->dispData[viewport]->state = DisplayerData::Steady;

        return;
    }

    QWebView *webView = dynamic_cast<QWebView*>(widget);
    if (webView) {
        QWebFrame *frame = webView->page()->mainFrame();
        frame->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
        frame->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);

        webView->installEventFilter(this);

        d->dispData.remove(webView);
        d->dispData[webView] = new DisplayerData;
        d->dispData[webView]->widget = webView;
        d->dispData[webView]->state = DisplayerData::Steady;

        return;
    }

    qWarning() << "FlickCharm only works on QAbstractScrollArea (and derived classes)";
    qWarning() << "or QWebView (and derived classes)";
}

void Displayer::deactivateFrom(QWidget *widget)
{
    QAbstractScrollArea *scrollArea = dynamic_cast<QAbstractScrollArea*>(widget);
    if (scrollArea) {
        QWidget *viewport = scrollArea->viewport();

        viewport->removeEventFilter(this);
        scrollArea->removeEventFilter(this);

        delete d->dispData[viewport];
        d->dispData.remove(viewport);

        return;
    }

    QWebView *webView = dynamic_cast<QWebView*>(widget);
    if (webView) {
        webView->removeEventFilter(this);

        delete d->dispData[webView];
        d->dispData.remove(webView);

        return;
    }
}
static QPoint scrollOffset(QWidget *widget)
{
    int x = 0, y = 0;

    QAbstractScrollArea *scrollArea = dynamic_cast<QAbstractScrollArea*>(widget);
    if (scrollArea) {
        x = scrollArea->horizontalScrollBar()->value();
        y = scrollArea->verticalScrollBar()->value();
    }

    QWebView *webView = dynamic_cast<QWebView*>(widget);
    if (webView) {
        QWebFrame *frame = webView->page()->mainFrame();
        x = frame->evaluateJavaScript("window.scrollX").toInt();
        y = frame->evaluateJavaScript("window.scrollY").toInt();
    }

    return QPoint(x, y);
}




static void setScrollOffset(QWidget *widget, const QPoint &p)
{
    QAbstractScrollArea *scrollArea = dynamic_cast<QAbstractScrollArea*>(widget);
    if (scrollArea) {
        scrollArea->horizontalScrollBar()->setValue(p.x());
        scrollArea->verticalScrollBar()->setValue(p.y());
    }

    QWebView *webView = dynamic_cast<QWebView*>(widget);
    QWebFrame *frame = webView ? webView->page()->mainFrame() : 0;
    if (frame)
        frame->evaluateJavaScript(QString("window.scrollTo(%1,%2);").arg(p.x()).arg(p.y()));
}

static QPoint deaccelerate(const QPoint &speed, int a = 1, int max = 64)
{
    int x = qBound(-max, speed.x(), max);
    int y = qBound(-max, speed.y(), max);
    x = (x == 0) ? x : (x > 0) ? qMax(0, x - a) : qMin(0, x + a);
    y = (y == 0) ? y : (y > 0) ? qMax(0, y - a) : qMin(0, y + a);
    return QPoint(x, y);
}


bool Displayer::eventFilter(QObject *object, QEvent *event)
{
    if (!object->isWidgetType())
        return false;

    QEvent::Type type = event->type();
    if (type != QEvent::MouseButtonPress &&
            type != QEvent::MouseButtonRelease &&
            type != QEvent::MouseMove)
        return false;

    QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
    if (!mouseEvent || mouseEvent->modifiers() != Qt::NoModifier)
        return false;

    QWidget *viewport = dynamic_cast<QWidget*>(object);
    DisplayerData *data = d->dispData.value(viewport);
    if (!viewport || !data || data->ignored.removeAll(event))
        return false;

    bool consumed = false;
    switch (data->state) {

    case DisplayerData::Steady:
        if (mouseEvent->type() == QEvent::MouseButtonPress)
            if (mouseEvent->buttons() == Qt::LeftButton) {
                consumed = true;
                data->state = DisplayerData::Pressed;
                data->pressPos = mouseEvent->pos();
                data->offset = scrollOffset(data->widget);
            }
        break;


case DisplayerData::Pressed:
        if (mouseEvent->type() == QEvent::MouseButtonRelease) {
            consumed = true;
            data->state = DisplayerData::Steady;

            QMouseEvent *event1 = new QMouseEvent(QEvent::MouseButtonPress,
                                                  data->pressPos, Qt::LeftButton,
                                                  Qt::LeftButton, Qt::NoModifier);
            QMouseEvent *event2 = new QMouseEvent(*mouseEvent);

            data->ignored << event1;
            data->ignored << event2;
            QApplication::postEvent(object, event1);
            QApplication::postEvent(object, event2);
        }
        if (mouseEvent->type() == QEvent::MouseMove) {
            consumed = true;
            data->state = DisplayerData::ManualScroll;
            data->dragPos = QCursor::pos();
            if (!d->ticker.isActive())
                d->ticker.start(20, this);
        }
        break;

    case DisplayerData::ManualScroll:
        if (mouseEvent->type() == QEvent::MouseMove) {
            consumed = true;
            QPoint delta = mouseEvent->pos() - data->pressPos;
            setScrollOffset(data->widget, data->offset - delta);
        }
        if (mouseEvent->type() == QEvent::MouseButtonRelease) {
            consumed = true;
            data->state = DisplayerData::AutoScroll;
        }
        break;

    case DisplayerData::AutoScroll:
        if (mouseEvent->type() == QEvent::MouseButtonPress) {
            consumed = true;
            data->state = DisplayerData::Stop;
            data->speed = QPoint(0, 0);
            data->pressPos = mouseEvent->pos();
            data->offset = scrollOffset(data->widget);
        }
        if (mouseEvent->type() == QEvent::MouseButtonRelease) {
            consumed = true;
            data->state = DisplayerData::Steady;
            data->speed = QPoint(0, 0);
        }
        break;

    case DisplayerData::Stop:
        if (mouseEvent->type() == QEvent::MouseButtonRelease) {
            consumed = true;
            data->state = DisplayerData::Steady;
        }
        if (mouseEvent->type() == QEvent::MouseMove) {
            consumed = true;
            data->state = DisplayerData::ManualScroll;
            data->dragPos = QCursor::pos();
            if (!d->ticker.isActive())
                d->ticker.start(20, this);
        }
        break;

    default:
        break;
    }
     return consumed;
}

void Displayer::timerEvent(QTimerEvent *event)
{
    int count = 0;
    QHashIterator<QWidget*, DisplayerData*> item(d->dispData);
    while (item.hasNext()) {
        item.next();
        DisplayerData *data = item.value();

        if (data->state == DisplayerData::ManualScroll) {
            count++;
            data->speed = QCursor::pos() - data->dragPos;
            data->dragPos = QCursor::pos();
        }

        if (data->state == DisplayerData::AutoScroll) {
            count++;
            data->speed = deaccelerate(data->speed);
            QPoint p = scrollOffset(data->widget);
            setScrollOffset(data->widget, p - data->speed);
            if (data->speed == QPoint(0, 0))
                data->state = DisplayerData::Steady;
        }
    }

    if (!count)
        d->ticker.stop();

    QObject::timerEvent(event);
}
