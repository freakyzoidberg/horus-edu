#ifndef EDTSCENE_H
#define EDTSCENE_H

#include <QGraphicsScene>
#include <QWidget>
# include			"../../../../Common/PluginManager.h"
# include			"../../../../Common/UserData.h"

class EDTScene : public QGraphicsScene, QWidget
{
public:
    EDTScene(QWidget *parent, PluginManager *pluginManager);

private:
    PluginManager	*_pluginManager;
};

#endif // EDTSCENE_H
