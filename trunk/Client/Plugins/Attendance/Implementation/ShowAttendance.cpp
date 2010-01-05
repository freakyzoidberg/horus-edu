#include "ShowAttendance.h"

ShowAttendance::ShowAttendance(QWidget *parent, UserData *user, AttendanceDataPlugin *attendanceDataPlugin)
{
    QBoxLayout          *mainLayout;
    QBoxLayout          *leftLayout;
    QBoxLayout          *rightLayout;
    QBoxLayout          *informationsLayout;
    QScrollArea         *scrollArea;
    QFrame		*informationsFrame;
    QLabel		*informationsTitle;
    QLabel		*actionsTitle;
    QPushButton         *applyButton;
    QPushButton         *okButton;
    QPushButton         *resetButton;
    QPushButton         *cancelButton;
    QWidget		*scrollWidget;

    _attendanceDataPlugin = attendanceDataPlugin;
    _user = user;
    mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(2);
    scrollArea = new QScrollArea(this);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidgetResizable(true);
    scrollWidget = new QWidget(this);
    leftLayout = new QBoxLayout(QBoxLayout::TopToBottom, scrollWidget);
    leftLayout->setSpacing(0);
    leftLayout->setMargin(0);
    leftLayout->addWidget(getAttendancesFrame());
    leftLayout->addWidget(new QWidget(scrollWidget), 1);
    scrollArea->setWidget(scrollWidget);
    mainLayout->addWidget(scrollArea);

    rightLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    rightLayout->setMargin(0);
    rightLayout->setSpacing(2);
    informationsFrame = new QFrame(this);
    informationsLayout = new QBoxLayout(QBoxLayout::TopToBottom, informationsFrame);
    informationsLayout->setSpacing(0);
    informationsLayout->setMargin(0);
    informationsFrame->setMinimumWidth(200);
    informationsTitle = new QLabel(tr("Informations:"), informationsFrame);
    informationsTitle->setProperty("isTitle", true);
    informationsTitle->setProperty("isRound", true);
    informationsLayout->addWidget(informationsTitle);
    rightLayout->addWidget(informationsFrame);
    actionsTitle = new QLabel(tr("Actions:"), this);
    actionsTitle->setProperty("isTitle", true);
    actionsTitle->setProperty("isRound", true);
    rightLayout->addWidget(actionsTitle);
    okButton = new QPushButton(QIcon(":/Icons/ok.png"), tr("OK"), this);
    rightLayout->addWidget(okButton);
    applyButton = new QPushButton(QIcon(":/Icons/save.png"), tr("Apply"), this);
    rightLayout->addWidget(applyButton);
    resetButton = new QPushButton(QIcon(":/Icons/reset.png"), tr("Reset"), this);
    rightLayout->addWidget(resetButton);
    cancelButton = new QPushButton(QIcon(":/Icons/back.png"), tr("Cancel"), this);
    rightLayout->addWidget(cancelButton);
    rightLayout->addWidget(new QWidget(this), 1);
    mainLayout->addLayout(rightLayout);
//    connect(okButton, SIGNAL(clicked()), this, SLOT(saved()));
//    connect(okButton, SIGNAL(clicked()), this, SLOT(exited()));
//    connect(applyButton, SIGNAL(clicked()), this, SLOT(saved()));
//    connect(resetButton, SIGNAL(clicked()), this, SLOT(reseted()));
//    connect(cancelButton, SIGNAL(clicked()), this, SLOT(exited()));
}

QWidget			*ShowAttendance::getAttendancesFrame()
{
    QLabel		*label;

    lessonFrame = new QFrame();
    lessonFrame->setProperty("isFormFrame", true);
    lessonMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, lessonFrame);
    lessonMainLayout->setSpacing(0);
    lessonMainLayout->setMargin(0);
    QString title = tr("Absences de ");
    title.append(_user->name());
    title.append(" ");
    title.append(_user->surname());
    lessonTitle = new QLabel(title, lessonFrame);
    lessonTitle->setProperty("isFormTitle", true);
    lessonMainLayout->addWidget(lessonTitle);
    lessonBottomLayout = new QGridLayout();
    lessonBottomLayout->setSpacing(4);
    lessonBottomLayout->setMargin(8);
    lessonBottomLayout->setColumnMinimumWidth(0, 100);
    lessonBottomLayout->setColumnMinimumWidth(5, 40);
    label = new QLabel(tr("Nom du Cour"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 0);
    label = new QLabel(tr("Date"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 1);
    label = new QLabel(tr("Heure Debut"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 2);
    label = new QLabel(tr("Heure Fin"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 3);
    label = new QLabel(tr("Type"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 4);
    label = new QLabel(tr("Effacer"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 5);
    QList<AttendanceData *> absList = _attendanceDataPlugin->attendance(_user);
    for (int i = 0; i < absList.size(); i++)
    {
            InfosAttendance *tmp = new InfosAttendance();
            tmp->name = new QLineEdit(this);
            tmp->name->setText(absList.at(i)->lesson());
            tmp->name->setDisabled(true);
            lessonBottomLayout->addWidget(tmp->name, i + 1, 0);
            tmp->date = new QDateEdit(this);
            tmp->date->setDate(absList.at(i)->date());
            tmp->date->setDisabled(true);
            lessonBottomLayout->addWidget(tmp->date, i + 1, 1);
            tmp->start = new QTimeEdit(this);
            tmp->start->setTime(absList.at(i)->startTime());
            tmp->start->setDisabled(true);
            lessonBottomLayout->addWidget(tmp->start, i + 1, 2);
            tmp->end = new QTimeEdit(this);
            tmp->end->setTime(absList.at(i)->endTime());
            tmp->end->setDisabled(true);
            lessonBottomLayout->addWidget(tmp->end, i + 1, 3);
            tmp->type = new QLineEdit(this);
            if (absList.at(i)->type() == 1)
                tmp->type->setText(tr("Absence"));
            else
                tmp->type->setText(tr("Retard"));
            tmp->type->setDisabled(true);
            lessonBottomLayout->addWidget(tmp->type, i + 1, 4);
            tmp->del = new QPushButton(QIcon(":/Icons/reset.png"),tr("Effacer"),this);
            lessonBottomLayout->addWidget(tmp->del, i + 1, 5);
            attendanceList.append(tmp);
    }
//
//    label = new QLabel(tr("Last name"), lessonFrame);
//    label->setProperty("isFormLabel", true);
//    lessonBottomLayout->addWidget(label, 0, 0);
//    QLineEdit *lastNameField = new QLineEdit(lessonFrame);
//    lastNameField->setText(user->name());
//    lastNameField->setDisabled(true);
//    lessonBottomLayout->addWidget(lastNameField, 0, 1);
//    label = new QLabel(tr("First name"), lessonFrame);
//    label->setProperty("isFormLabel", true);
//    lessonBottomLayout->addWidget(label, 0, 2);
//    QLineEdit *firstNameField = new QLineEdit(user->surname(), lessonFrame);
//    firstNameField->setText(user->surname());
//    firstNameField->setDisabled(true);
//    lessonBottomLayout->addWidget(firstNameField, 0, 3);
//    label = new QLabel(tr("Date"), lessonFrame);
//    label->setProperty("isFormLabel", true);
//    lessonBottomLayout->addWidget(label, 1, 0);
//    dateAttendance = new QDateEdit(lessonFrame);
//    dateAttendance->setDate(QDate::currentDate());
//    dateAttendance->setCalendarPopup(true);
//    connect(dateAttendance, SIGNAL(dateChanged(const QDate &)), this, SLOT(dChanged(const QDate &)));
//    lessonBottomLayout->addWidget(dateAttendance, 1, 1);
//    label = new QLabel(tr("Type"), lessonFrame);
//    label->setProperty("isFormLabel", true);
//    lessonBottomLayout->addWidget(label, 1, 2);
//    typeList = new QComboBox(lessonFrame);
//    typeList->addItem(tr("Absence"), 1);
//    typeList->addItem(tr("Retard"), 2);
//    lessonBottomLayout->addWidget(typeList, 1, 3);
//
//    lessonMainLayout->addLayout(lessonBottomLayout);
//    cours = new CourPanel(_scheduleDataPlugin->schedule(node), dateAttendance->date());
//    lessonMainLayout->addWidget(cours);
    lessonMainLayout->addLayout(lessonBottomLayout);
    return (lessonFrame);
}
