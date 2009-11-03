#ifndef ADDEVENTWIDGET_H
#define ADDEVENTWIDGET_H

#include <QWidget>
#include <QPushButton>

class AddEventWidget : public QWidget
{
public:
    AddEventWidget();
    QPushButton     *cancel()   { return _cancel; }
    QPushButton     *save()   { return _save; }

private:
     QPushButton    *_cancel;
     QPushButton    *_save;
};

#endif // ADDEVENTWIDGET_H
