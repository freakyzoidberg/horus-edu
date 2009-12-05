#include "EdtScene.h"

#define SCENE_WIDTH 700

EDTScene::EDTScene(PluginManager *pluginManager, TreeData *treedata) : _pluginManager(pluginManager)
{
    qDebug() << __FILE__ <<":" << __LINE__ << "EDTScene constructor called for node " << treedata->id();
    _SD = pluginManager->findPlugin<ScheduleDataPlugin*>()->schedule(treedata);



}
