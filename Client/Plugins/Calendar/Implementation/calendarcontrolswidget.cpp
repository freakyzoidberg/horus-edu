#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QHashIterator>

#include "CalendarCore.h"
#include "calendarcontrolswidget.h"
#include "CalendarMainFrame.h"

CalendarControlsWidget::CalendarControlsWidget()
{
     _monthly = new QPushButton(tr("Month"));
     _daily = new QPushButton(tr("Day"));
     _weekly = new QPushButton(tr("Week"));
     _planning = new QPushButton(tr("Planning"));

     _groupList = new QComboBox;
     initGroupList();
     _userList = new QComboBox;
     initUserList("ALL");

     _go = new QPushButton(tr("Rechercher"));
     _userName = new QLineEdit;

     _addEvent = new QPushButton("add an event");

     QGridLayout *controlsLayout = new QGridLayout;
     controlsLayout->setMargin(0);
     controlsLayout->setSpacing(0);

     controlsLayout->addWidget(_addEvent, 0, 3);

     controlsLayout->addWidget(_groupList, 0, 0);
     controlsLayout->addWidget(_userList, 0, 1);
     controlsLayout->addWidget(_userName, 1, 0);
     controlsLayout->addWidget(_go, 1, 1);

     controlsLayout->addWidget(_monthly, 2, 0);
     controlsLayout->addWidget(_daily, 2, 1);
     controlsLayout->addWidget(_weekly, 2, 2);
     controlsLayout->addWidget(_planning, 2, 3);

     //connect combo box signals
     connect(_groupList, SIGNAL(activated(int)), this, SLOT(selectGroup(int)));
     connect(_userList, SIGNAL(activated(int)), this, SLOT(selectUser(int)));

     this->setLayout(controlsLayout);
}

void CalendarControlsWidget::setMonth(int month)
{
    selectedDate = QDate(selectedDate.year(), month + 1, selectedDate.day());
}

 void CalendarControlsWidget::setYear(QDate date)
{
    selectedDate = QDate(date.year(), selectedDate.month(), selectedDate.day());
}


 void   CalendarControlsWidget::initGroupList()
 {
    QHash<quint32, TreeData *> *groups = CalendarCore::CalendarCoreInstance()->getNodeOfType("GROUP");
    QHashIterator<quint32, TreeData *> i(*groups);

    while (i.hasNext())
    {
        i.next();
        _groupList->addItem(i.value()->name(), QVariant(i.value()->id()));
    }
    delete groups;
}

 void   CalendarControlsWidget::initUserList(const QString & groupName)
 {
    QHash<quint32, UserData *>  *users = CalendarCore::CalendarCoreInstance()->usersName(groupName);
    QHashIterator<quint32, UserData *> i(*users);

    while (i.hasNext())
    {
        i.next();
        _userList->addItem(i.value()->name() + " " + i.value()->surname(), QVariant(i.value()->id()));
    }
    delete users;
 }

  void               CalendarControlsWidget::selectGroup(int index)
  {
    QVariant    tmp;
    int         group_id;

    tmp = _groupList->itemData(index);
    group_id = tmp.toInt();

    //empty the user list
    _userList->clear();

    //recup all users, search them where node == group_id
    QHash<quint32, UserData *>  *users = CalendarCore::CalendarCoreInstance()->usersName("ALL");
    QHashIterator<quint32, UserData *> i(*users);

    while (i.hasNext())
    {
        i.next();
        if ((i.value()->status() != Data::EMPTY)
            && (i.value()->node()->id() == group_id))
            _userList->addItem(i.value()->name() + " "
                           + i.value()->surname(), QVariant(i.value()->id()));
    }
    delete users;
  }

  void               CalendarControlsWidget::selectUser(int index)
  {
    QVariant    tmp;
    int         user_id;

    tmp = _userList->itemData(index);
    user_id = tmp.toInt();
    qDebug() << "user:" << user_id;
}

