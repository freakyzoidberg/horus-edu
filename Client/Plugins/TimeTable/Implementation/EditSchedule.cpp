#include "EditSchedule.h"

EditSchedule::EditSchedule(PluginManager *pluginManager)
{
    vLayout = new QVBoxLayout(this);
    _classList = new QComboBox();
    vLayout->addWidget(_classList);
    hLayout = new QHBoxLayout();
    _startDate = new QCalendarWidget();
    _endDate = new QCalendarWidget();
    hLayout->addWidget(_startDate);
    hLayout->addWidget(_endDate);
    vLayout->addLayout(hLayout);
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
