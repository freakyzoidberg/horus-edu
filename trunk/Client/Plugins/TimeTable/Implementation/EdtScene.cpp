#include "EdtScene.h"

#define SCENE_WIDTH 700

EDTScene::EDTScene(PluginManager *pluginManager, TreeData *treedata) : _pluginManager(pluginManager)
{
    _SD = pluginManager->findPlugin<ScheduleDataPlugin*>()->schedule(treedata);
}
