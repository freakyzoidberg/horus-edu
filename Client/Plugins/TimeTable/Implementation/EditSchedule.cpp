#include "EditSchedule.h"

EditSchedule::EditSchedule(PluginManager *pluginManager)
{
    vLayout = new QVBoxLayout(this);
    _classList = new QComboBox();
    vLayout->addWidget(_classList);
    titleLayout = new QHBoxLayout();
    QLabel *lStart = new QLabel(tr("Début"));
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
    //line->setGeometry(QRect(290, 430, 411, 16));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    hLayout2->addWidget(line, 3);
    _addException = new QPushButton("+");
    _addException->setFlat(true);
    hLayout2->addWidget(_addException, 1);
    fillClasses(pluginManager->findPlugin<TreeDataPlugin*>());
}

void    EditSchedule::fillClasses(TreeDataPlugin *treePlugin)
{
        QList<Data*> datas = treePlugin->allDatas();

        for (int i = 0, j = 0; i < datas.size(); ++i)
        {
                TreeData    *tmp = qobject_cast<TreeData *>(datas.at(i));
                if (tmp->type() == "GRADE")
                {
                    _classList->addItem(tmp->name(), tmp->id());
                }
        }

}


