#ifndef EDTSCENE_H
#define EDTSCENE_H

#include <QGraphicsScene>
#include <QWidget>
# include			"../../../../Common/PluginManager.h"
# include			"../../../../Common/UserData.h"


class EDTScene : public QGraphicsScene
{
	Q_OBJECT

public:
	EDTScene(PluginManager *pluginManager);

private:
    PluginManager	*_pluginManager;

};

#endif // EDTSCENE_H
