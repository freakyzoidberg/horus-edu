#include <QPushButton>
#include <QGridLayout>
#include <QVariant>

#include "addeventwindows.h"

AddEventWindows    *AddEventWindows::_instance = NULL;

AddEventWindows::AddEventWindows() : QDockWidget()
{
    setFloating(true);
    setFeatures(QDockWidget::DockWidgetClosable);
    setMaximumSize(260, 120);
    setMinimumSize(260, 120);

    this->_windowTitle = new QLabel(tr(" Add an event."), this);
    _windowTitle->setGeometry(0, 10, 100, 20);

    this->_date = new QLabel(this);
    this->_date->setGeometry(46, 25, 210, 20);

    this->_dateTitle = new QLabel(tr("Date:"), this);
    _dateTitle->setGeometry(2, 25, 45, 20);

    this->_title = new QLineEdit(this);
    _title->setGeometry(45, 46, 200, 20);

    this->_titleLabel = new QLabel(tr("Title:"), this);
    _titleLabel->setGeometry(2, 46, 46, 20);

    this->_details = new Label(tr("View event's details."), this);
    _details->setGeometry(2, 68, 240, 20);

    this->_save = new QPushButton(tr("OK"), this);
    _save->setGeometry(220, 90, 30, 20);
}


AddEventWindows    *AddEventWindows::AddEventWindowsInstance()
{
   if (!_instance)
     _instance = new AddEventWindows();
   return _instance;
}

void    AddEventWindows::setDate(QDate & date, int hour)
{
    QVariant hourS(hour);

    QVariant hourE;

    if (hour + 1 == 24)
        hourE.setValue(0);
    else
        hourE.setValue(hour + 1);

    //ex : Mon 02 Dec, 15h00 - 16h00
   _date->setText(date.toString("ddd dd MMM, " + hourS.toString() + ":00 - "
                                + hourE.toString() + ":00"));
}


