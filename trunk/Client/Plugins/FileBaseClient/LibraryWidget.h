#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
class PluginManager;

class LibraryWidget : public QWidget
{
public:
	LibraryWidget(PluginManager* pluginManager);
private:
	QHBoxLayout*	_layout;
};

#endif // LIBRARYWIDGET_H
