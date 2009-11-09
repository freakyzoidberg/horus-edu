#ifndef TRANSFERTPLUGIN_H
#define TRANSFERTPLUGIN_H

#include "../../DisplayablePlugin.h"
#include "TransfertList.h"

class TransfertPlugin : public DisplayablePlugin
{
	Q_OBJECT
	Q_INTERFACES(DisplayablePlugin)

public:
	const QString			pluginName()    const { return "Library"; }
	const QString			pluginVersion() const { return "1"; }

	inline QWidget*			getWidget()	{ return new TransfertList; }
	inline const QString	getDisplayableName() const { return tr("File transferts"); }
//	inline QIcon getIcon() const { return (QIcon()); }
//	inline int getOrder() const { return (50); }
//	inline bool operator<(DisplayablePlugin &right) const { return (this->getOrder() < right.getOrder()); }
};

#endif // TRANSFERTPLUGIN_H
