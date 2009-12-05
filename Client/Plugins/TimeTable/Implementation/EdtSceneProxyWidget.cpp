#include "EdtSceneProxyWidget.h"

EdtSceneProxyWidget::EdtSceneProxyWidget(PluginManager *pluginManager) : _pluginManager(pluginManager)
{

    _scene = new EDTScene(pluginManager);
    this->setScene(_scene);
}
