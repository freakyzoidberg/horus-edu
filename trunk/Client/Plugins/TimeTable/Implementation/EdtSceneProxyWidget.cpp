#include "EdtSceneProxyWidget.h"

EdtSceneProxyWidget::EdtSceneProxyWidget(PluginManager *pluginManager, TreeData *treedata) : _pluginManager(pluginManager)
{

    _scene = new EDTScene(pluginManager, treedata);
    this->setScene(_scene);
}

EdtSceneProxyWidget::~EdtSceneProxyWidget()
{
    if (_scene)
        delete _scene;
}
