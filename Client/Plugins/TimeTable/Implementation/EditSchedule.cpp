#include "EditSchedule.h"

EditSchedule::EditSchedule(ScheduleDataPlugin *sd, TreeDataPlugin *td, int id, int type)
{
    sdp = sd;
    tdp = td;
    vLayout = new QVBoxLayout(this);
    _classList = new QComboBox();
    vLayout->addWidget(_classList);
    titleLayout = new QHBoxLayout();
    QLabel *lStart = new QLabel(tr("Debut"));
    QLabel *lEnd = new QLabel(tr("Fin"));
    titleLayout->addWidget(lStart);
    titleLayout->addWidget(lEnd);
    vLayout->addLayout(titleLayout);
    hLayout = new QHBoxLayout();
    _startDate = new QCalendarWidget();
    _endDate = new QCalendarWidget();
    hLayout->addWidget(_startDate);
    hLayout->addWidget(_endDate);
    vLayout->addLayout(hLayout);
    hLayout2 = new QHBoxLayout(); 
    line = new QFrame();
    line->setObjectName(QString::fromUtf8("line"));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    hLayout2->addWidget(line, 14);
    _addException = new QPushButton("+");
    _addException->setFlat(true);
    hLayout2->addWidget(_addException, 1);
    if (type == 1)
        fillForm(id);
    vLayout->addLayout(hLayout2);
    connect(_addException, SIGNAL(clicked()), this, SLOT(addException()));
    fillClasses();
}

void    EditSchedule::fillForm(int id)
{
    ScheduleData *sd = sdp->schedule(tdp->node(id));
    _startDate->setSelectedDate(sd->startDate());
    _endDate->setSelectedDate(sd->endDate());
}

void    EditSchedule::fillClasses()
{
        QList<Data*> datas = tdp->allDatas();

        for (int i = 0, j = 0; i < datas.size(); ++i)
        {
                TreeData    *tmp = qobject_cast<TreeData *>(datas.at(i));
                if (tmp->type() == "GRADE")
                {
                    _classList->addItem(tmp->name(), tmp->id());
                }
        }

}

void    EditSchedule::addException()
{

}
