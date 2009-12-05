#ifndef EDTSCENE_H
#define EDTSCENE_H

#include <QGraphicsScene>
#include <QWidget>
# include			"../../../../Common/PluginManager.h"
# include			"../../../../Common/UserData.h"
# include			"../../../../Common/TreeData.h"
# include                        "../../../../Common/ScheduleData.h"

class EDTScene : public QGraphicsScene
{
	Q_OBJECT

public:
        EDTScene(PluginManager *pluginManager, TreeData *treedata);

private:
    PluginManager	*_pluginManager;
    ScheduleData        *_SD;

};

#endif // EDTSCENE_H
