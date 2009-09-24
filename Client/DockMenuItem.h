#ifndef DOCKMENUITEM_H
#define DOCKMENUITEM_H

#include <QPushButton>

#include "DisplayablePlugin.h"

class DockMenuItem : public QPushButton
{
public:
    inline DockMenuItem(DisplayablePlugin* plugin, const QString title, QIcon icon) : QPushButton(icon, title) { _plugin = plugin; }
    inline QWidget* getPluginWidget() const { return _plugin->getWidget(); }

private:
    DisplayablePlugin* _plugin;
};

#endif // DOCKMENUITEM_H
