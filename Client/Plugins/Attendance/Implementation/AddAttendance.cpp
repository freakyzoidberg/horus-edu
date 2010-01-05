/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "AddAttendance.h"

AddAttendance::AddAttendance(QWidget *parent, TreeData *tree, UserData *_user, ScheduleDataPlugin *event, AttendanceDataPlugin *attendanceDataPlugin)
{
    user = _user;
    _scheduleDataPlugin = event;
    _attendanceDataPlugin = attendanceDataPlugin;
    node = tree;
    cours = 0;
    setupUi();
    //connect(dateAttendance, SIGNAL(dateChanged(const QDate &)), this, SLOT(dChanged(const QDate &)));
    //connect(allCourse, SIGNAL(stateChanged(int)), this, SLOT(allChecked(int)));
    //fillCourse(event);
    proxyModel = new QSortFilterProxyModel();
    //userList->setModel(new UserPerClass(user->allDatas(), -10, this));
}

void    AddAttendance::fillCourse(ScheduleDataPlugin *event)
{
//    courList.append(new CourPanel("Mathematiques"));
//    courList.append(new CourPanel("Physique"));
//    courList.append(new CourPanel("Histoire"));
//    courList.append(new CourPanel("Anglais"));
//
//    for (int i = 0; i < courList.size(); i++)
//    {
//        rightSide->addWidget(courList.at(i), i + 1, 0);
//    }
//    absLayout->addLayout(rightSide);
//    absLayout->setAlignment(rightSide, Qt::AlignTop);
//    absLayout->setStretch(0, 1);
//    absLayout->setStretch(1, 3);
//    rightSide->addLayout(buttonLayout->layout(), 5, 0);
}

void    AddAttendance::setupUi()
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
    leftLayout->addWidget(getLessonsFrame());
    leftLayout->addWidget(new QWidget(scrollWidget), 1);
    // leftLayout->addWidget(new CourPanel(_scheduleDataPlugin->schedule(node), dateAttendance->date()));
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
    connect(okButton, SIGNAL(clicked()), this, SLOT(saved()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(exited()));
    connect(applyButton, SIGNAL(clicked()), this, SLOT(saved()));
    connect(resetButton, SIGNAL(clicked()), this, SLOT(reseted()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(exited()));

//    absLayout = new QHBoxLayout(this);
//    rightSide = new QGridLayout();
//    leftSide = new QVBoxLayout();
//    buttonLayout = new QHBoxLayout();
//    userName = new QLineEdit();
//    leftSide->addWidget(userName);
//    classList = new QComboBox();
//    leftSide->addWidget(classList);
//    userList = new QListView();
//    leftSide->addWidget(userList);
//    absLayout->addLayout(leftSide);
//    dateAttendance = new QDateEdit();
//    dateAttendance->setMaximumSize(100, 30);
//    dateAttendance->setDate(QDate::currentDate());
//    rightSide->addWidget(dateAttendance);
//    rightSide->setSpacing(0);
//    allCourse = new QCheckBox(tr("Check All"));
//    okButton = new QPushButton(tr("Valider"));
//    buttonLayout->addWidget(allCourse);
//    buttonLayout->addWidget(okButton);
}

QWidget			*AddAttendance::getLessonsFrame()
{
    QLabel		*label;

    lessonFrame = new QFrame();
    lessonFrame->setProperty("isFormFrame", true);
    lessonMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, lessonFrame);
    lessonMainLayout->setSpacing(0);
    lessonMainLayout->setMargin(0);
    lessonTitle = new QLabel(tr("Absence informations"), lessonFrame);
    lessonTitle->setProperty("isFormTitle", true);
    lessonMainLayout->addWidget(lessonTitle);
    lessonBottomLayout = new QGridLayout();
    lessonBottomLayout->setSpacing(4);
    lessonBottomLayout->setMargin(8);
    lessonBottomLayout->setColumnMinimumWidth(0, 150);

    label = new QLabel(tr("Last name"), lessonFrame);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 0);
    QLineEdit *lastNameField = new QLineEdit(lessonFrame);
    lastNameField->setText(user->name());
    lastNameField->setDisabled(true);
    lessonBottomLayout->addWidget(lastNameField, 0, 1);
    label = new QLabel(tr("First name"), lessonFrame);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 2);
    QLineEdit *firstNameField = new QLineEdit(user->surname(), lessonFrame);
    firstNameField->setText(user->surname());
    firstNameField->setDisabled(true);
    lessonBottomLayout->addWidget(firstNameField, 0, 3);
    label = new QLabel(tr("Date"), lessonFrame);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 1, 0);
    dateAttendance = new QDateEdit(lessonFrame);
    dateAttendance->setDate(QDate::currentDate());
    dateAttendance->setCalendarPopup(true);
    connect(dateAttendance, SIGNAL(dateChanged(const QDate &)), this, SLOT(dChanged(const QDate &)));
    lessonBottomLayout->addWidget(dateAttendance, 1, 1);
    label = new QLabel(tr("Type"), lessonFrame);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 1, 2);
    typeList = new QComboBox(lessonFrame);
    typeList->addItem(tr("Absence"), 1);
    typeList->addItem(tr("Retard"), 2);
    lessonBottomLayout->addWidget(typeList, 1, 3);

//    lessonBottomLayout->addWidget(firstNameField, 0, 3);
//    label = new QLabel(tr("Birth date"), lessonFrame);
//    label->setProperty("isFormLabel", true);
//    lessonBottomLayout->addWidget(label, 1, 0);
//    birthDateField = new QDateEdit(lessonFrame);
//    birthDateField->setDate(QDate::currentDate());
//    birthDateField->setCalendarPopup(true);
//    birthDateField->setDisplayFormat(tr("dd/MM/yy"));
//    lessonBottomLayout->addWidget(birthDateField, 1, 1);
//    label = new QLabel(tr("Birth place"), lessonFrame);
//    label->setProperty("isFormLabel", true);
//    lessonBottomLayout->addWidget(label, 1, 2);
//    birthPlaceField = new QLineEdit(lessonFrame);
//    completer = new QCompleter(_userDataPlugin->listModel(), this);
//    completer->setCompletionColumn(4);
//    completer->setCaseSensitivity(Qt::CaseInsensitive);
//    birthPlaceField->setCompleter(completer);
//    lessonBottomLayout->addWidget(birthPlaceField, 1, 3);
//    label = new QLabel(tr("Gender"), lessonFrame);
//    label->setProperty("isFormLabel", true);
//    lessonBottomLayout->addWidget(label, 2, 0);

    lessonMainLayout->addLayout(lessonBottomLayout);
    cours = new CourPanel(_scheduleDataPlugin->schedule(node), dateAttendance->date());
    lessonMainLayout->addWidget(cours);
    return (lessonFrame);
}

void    AddAttendance::dChanged(const QDate &date)
{
    if (cours != 0)
    {
        lessonMainLayout->removeWidget(cours);
        cours->close();
        cours = 0;
    }
    cours = new CourPanel(_scheduleDataPlugin->schedule(node), dateAttendance->date());
    lessonMainLayout->addWidget(cours);

}

void    AddAttendance::allChecked(int state)
{
//    for (int i = 0; i < courList.size(); i++)
//    {
//        if (state == 2)
//            courList[i]->absenceCheck->setChecked(true);
//        else
//            courList[i]->absenceCheck->setChecked(false);
//    }
}



void    AddAttendance::saved()
{
    for (int i = 0; i < cours->lessonList.size(); i++)
    {
        if (cours->lessonList.at(i)->state->isChecked() == true)
        {
            AttendanceData *a = _attendanceDataPlugin->newAttendance(user, dateAttendance->date(), cours->lessonList.at(i)->name->text());
            a->setDate(dateAttendance->date());
            a->setLesson(cours->lessonList.at(i)->name->text());
            a->setStartTime(cours->lessonList.at(i)->start->time());
            a->setEndTime(cours->lessonList.at(i)->end->time());
            a->setType(typeList->itemData(typeList->currentIndex()).toInt());
            a->create();
        }
    }
}

void    AddAttendance::exited()
{
        emit exit();
}

void    AddAttendance::reseted()
{

}
