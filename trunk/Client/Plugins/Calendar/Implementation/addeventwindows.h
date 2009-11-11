#ifndef ADDEVENTWINDOWS_H
#define ADDEVENTWINDOWS_H

#include <QDockWidget>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QDate>

#include "label.h"

class AddEventWindows : public QDockWidget
{
public:
    static  AddEventWindows        *AddEventWindowsInstance();
    void    setDate(QDate &, int);
    Label   *details()              { return _details; }

private:
                                AddEventWindows();

    static  AddEventWindows        *_instance;
    QLineEdit                   *_title;
    QLabel                  *_titleLabel;

    QLabel  *_dateTitle;
    QLabel  *_date;

    Label  *_details;

    QPushButton *_save;
    QLabel  *_windowTitle;
};

#endif // ADDEVENTWINDOWS_H
