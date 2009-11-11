#ifndef LIBRARYPLUGIN_H
#define LIBRARYPLUGIN_H

#include "../../DisplayablePlugin.h"
#include "LibraryWidget.h"

class LibraryPlugin : public DisplayablePlugin
{
	Q_OBJECT
	Q_INTERFACES(DisplayablePlugin)

public:
	const QString			pluginName()    const { return "Library"; }
	const QString			pluginVersion() const { return "1"; }

	inline QWidget*			getWidget()	{ return new LibraryWidget(pluginManager); }
	inline const QString	getDisplayableName() const { return tr("Library"); }
	inline QIcon getIcon() const { return (QIcon(":Icons/lib-icon.png")); }
//	inline int getOrder() const { return (50); }
//	inline bool operator<(DisplayablePlugin &right) const { return (this->getOrder() < right.getOrder()); }
};

#endif // LIBRARYPLUGIN_H
