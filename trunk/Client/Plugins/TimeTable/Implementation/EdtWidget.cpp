#include "EdtWidget.h"
# include <QDebug>
EdtWidget::EdtWidget(PluginManager *pluginManager) : _pluginManager(pluginManager)
{
    _sceneWidget = NULL;
    MainLayout = new QHBoxLayout();
    MainLayout->setSpacing(0);
    MainLayout->setMargin(2);
}


void EdtWidget::createScene(TreeData *td)
{
    qDebug() << __FILE__ <<":" << __LINE__ << "slot:createScene() called";
    if (_sceneWidget)
        delete _sceneWidget;
    _sceneWidget = new EdtSceneProxyWidget(_pluginManager, td);

}
