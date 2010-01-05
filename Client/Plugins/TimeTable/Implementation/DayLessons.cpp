#include "DayLessons.h"
#include <QBoxLayout>

DayLessons::DayLessons(ScheduleDataPlugin *sdp, UserData *user)
{
    QBoxLayout *mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(2);
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidgetResizable(true);
    QWidget *scrollWidget = new QWidget(this);
    QBoxLayout *leftLayout = new QBoxLayout(QBoxLayout::TopToBottom, scrollWidget);
    leftLayout->setSpacing(0);
    leftLayout->setMargin(0);


    QFrame *lessonFrame = new QFrame(this);
    lessonFrame->setProperty("isFormFrame", true);
    QBoxLayout *lessonMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, lessonFrame);
    lessonMainLayout->setSpacing(0);
    lessonMainLayout->setMargin(0);
    QGridLayout *lessonBottomLayout = new QGridLayout();
    lessonBottomLayout->setSpacing(4);
    lessonBottomLayout->setMargin(8);
    ScheduleData *schedule = sdp->schedule(user->studentClass());
    if (schedule != 0)
    {
        QLabel *label = new QLabel(tr("Nom du Cour"), lessonFrame);
        label->setProperty("isFormLabel", true);
        lessonBottomLayout->addWidget(label, 0, 0);
        label = new QLabel(tr("Heure Debut"), lessonFrame);
        label->setProperty("isFormLabel", true);
        lessonBottomLayout->addWidget(label, 0, 1);
        label = new QLabel(tr("Heure Fin"), lessonFrame);
        label->setProperty("isFormLabel", true);
        lessonBottomLayout->addWidget(label, 0, 2);

        for (int i = 0; i < schedule->scheduleEvents().size(); i++)
        {
            if (schedule->scheduleEvents().at(i)->getJWeek() == QDate::currentDate().dayOfWeek())
            {
                InfosLesson *tmp = new InfosLesson();
                tmp->name = new QLineEdit(lessonFrame);
                lessonBottomLayout->addWidget(tmp->name, i + 1, 0);
                tmp->name->setText(schedule->scheduleEvents().at(i)->getName());
                tmp->name->setDisabled(true);
                tmp->start = new QTimeEdit(lessonFrame);
                tmp->start->setTime(schedule->scheduleEvents().at(i)->getHStart());
                tmp->start->setDisabled(true);
                lessonBottomLayout->addWidget(tmp->start, i + 1, 1);
                tmp->end = new QTimeEdit(lessonFrame);
                tmp->end->setTime(schedule->scheduleEvents().at(i)->getHEnd());
                tmp->end->setDisabled(true);
                lessonBottomLayout->addWidget(tmp->end, i + 1, 2);
                lessonList.append(tmp);
            }
        }
    }
    else
    {
        QLabel *label = new QLabel(tr("Vous n\'avez pas de cours aujourdhui"), lessonFrame);
        label->setProperty("isFormLabel", true);
        lessonBottomLayout->addWidget(label, 0, 0);
    }
    lessonMainLayout->addLayout(lessonBottomLayout);
    leftLayout->addWidget(lessonFrame);
    leftLayout->addWidget(new QWidget(scrollWidget), 1);
    scrollArea->setWidget(scrollWidget);
    mainLayout->addWidget(scrollArea);
}

