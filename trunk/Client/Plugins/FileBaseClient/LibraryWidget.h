#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>
class PluginManager;

class LibraryWidget : public QWidget
{
public:
	LibraryWidget(PluginManager* pluginManager);
};

#endif // LIBRARYWIDGET_H
