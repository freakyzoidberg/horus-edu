#include "CourPanel.h"


CourPanel::CourPanel(ScheduleData *schedule, QDate date)
{

//    QFrame *lessonFrame = new QFrame(this);
//    lessonFrame->setProperty("isFormFrame", true);
    lessonMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    lessonMainLayout->setSpacing(0);
    lessonMainLayout->setMargin(0);
    QLabel *lessonTitle = new QLabel(tr("Cours informations"), this);
    lessonTitle->setProperty("isFormTitle", true);
    lessonMainLayout->addWidget(lessonTitle);
    lessonBottomLayout = new QGridLayout();
    lessonBottomLayout->setSpacing(4);
    lessonBottomLayout->setMargin(8);
    if (schedule != 0)
    {
        bool haveEvent = false;
        if (schedule->scheduleEvents().size() == 0)
        {
            addLesson();
        }
        else
        {
            for (int i = 0; i < schedule->scheduleEvents().size(); i++)
            {
                if (schedule->scheduleEvents().at(i)->getJWeek() == date.dayOfWeek())
                {
                    haveEvent = true;
                }
            }
            if (haveEvent == true)
               getScheduleLesson(schedule, date.dayOfWeek());
            else
                addLesson();
        }
    }
    else
    {
        addLesson();
    }
    lessonMainLayout->addLayout(lessonBottomLayout);
}

void    CourPanel::addLesson()
{
    QLabel *label = new QLabel(tr("Nom du Cour"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 0);
    label = new QLabel(tr("Heure Debut"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 1);
    label = new QLabel(tr("Heure Fin"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 2);
    label = new QLabel(tr("Appliquer"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 3);
    InfosLesson *tmp = new InfosLesson();
    tmp->name = new QLineEdit(this);
    lessonBottomLayout->addWidget(tmp->name, 1, 0);
    tmp->start = new QTimeEdit(this);
    lessonBottomLayout->addWidget(tmp->start, 1, 1);
    tmp->end = new QTimeEdit(this);
    lessonBottomLayout->addWidget(tmp->end, 1, 2);
    tmp->state = new QCheckBox(this);
    lessonBottomLayout->addWidget(tmp->state, 1, 3);
    tmp->state->setChecked(true);
    tmp->state->setDisabled(true);
    lessonList.append(tmp);
}

void    CourPanel::getScheduleLesson(ScheduleData *schedule, int day)
{
    QLabel *label = new QLabel(tr("Nom du Cour"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 0);
    label = new QLabel(tr("Heure Debut"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 1);
    label = new QLabel(tr("Heure Fin"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 2);
    label = new QLabel(tr("Appliquer"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 3);
    for (int i = 0; i < schedule->scheduleEvents().size(); i++)
    {
        if (schedule->scheduleEvents().at(i)->getJWeek() == day)
        {
            InfosLesson *tmp = new InfosLesson();
            tmp->name = new QLineEdit(this);
            lessonBottomLayout->addWidget(tmp->name, i + 1, 0);
            tmp->name->setText(schedule->scheduleEvents().at(i)->getName());
            tmp->name->setDisabled(true);
            tmp->start = new QTimeEdit(this);
            tmp->start->setTime(schedule->scheduleEvents().at(i)->getHStart());
            tmp->start->setDisabled(true);
            lessonBottomLayout->addWidget(tmp->start, i + 1, 1);
            tmp->end = new QTimeEdit(this);
            tmp->end->setTime(schedule->scheduleEvents().at(i)->getHEnd());
            tmp->end->setDisabled(true);
            lessonBottomLayout->addWidget(tmp->end, i + 1, 2);
            tmp->state = new QCheckBox(this);
            lessonBottomLayout->addWidget(tmp->state, i + 1, 3);
            lessonList.append(tmp);
        }
    }
}
