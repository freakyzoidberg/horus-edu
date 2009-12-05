#ifndef EDTSCENEPROXYWIDGET_H
#define EDTSCENEPROXYWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
# include			"../../../../Common/PluginManager.h"
# include			"../../../../Common/UserData.h"
# include			"../../../../Common/TreeData.h"
#include "EdtScene.h"

class EdtSceneProxyWidget : public QGraphicsView
{
public:
    EdtSceneProxyWidget(PluginManager *pluginManager, TreeData *treedata);
    ~EdtSceneProxyWidget();
    ScheduleData *getScheduleData();

private:
    PluginManager	*_pluginManager;
    EDTScene            *_scene;
};

#endif // EDTSCENEPROXYWIDGET_H
