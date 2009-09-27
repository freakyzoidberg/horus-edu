#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QtPlugin>
#include <QHash>

#include "../../../DisplayablePlugin.h"

class MainFrameWidget;

class MainFrame : public DisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(DisplayablePlugin)

public:
    // INTERFACE Plugin
    inline const QString    pluginName() const    { return "MainFrame"; }
    inline const QString    pluginVersion() const { return "0.1"; }
    bool                    canLoad() const;
    void                    load();

    // INTERFACE DisplayablePlugin
    inline const QString    getDisplayableName() const { return tr("Main Board"); }
    QWidget*                getWidget();
	int						getOrder() const;
	QIcon					getIcon() const;

private slots:
    void                    courseClicked();
};

#endif // MAINFRAME_H
