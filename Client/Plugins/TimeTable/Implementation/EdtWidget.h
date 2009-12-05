#ifndef EDTWIDGET_H
#define EDTWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include "../../../../Common/ScheduleData.h"

#include "EdtSceneProxyWidget.h"

class EdtWidget : public QWidget
{
    Q_OBJECT

public:
    EdtWidget(PluginManager *pluginManager);

public slots:
    void createScene(TreeData *);

private:
    PluginManager	*_pluginManager;
    EdtSceneProxyWidget *_sceneWidget;
    QHBoxLayout         *MainLayout;
};

#endif // EDTWIDGET_H
