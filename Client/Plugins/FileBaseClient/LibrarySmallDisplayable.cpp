#include		"LibrarySmallDisplayable.h"

#include		<QLabel>

const QString	LibrarySmallDisplayable::pluginName() const
{
	return ("LibrarySmallDisplayable");
}

const QString	LibrarySmallDisplayable::pluginVersion() const
{
	return ("0.1");
}

QWidget			*LibrarySmallDisplayable::getWidget()
{
	return (new QLabel(tr("Fill me with the new files in library.")));
}

const QString	LibrarySmallDisplayable::getDisplayableName() const
{
	return (tr("New files"));
}

QIcon			LibrarySmallDisplayable::getIcon() const
{
	return (QIcon(":/Icons/lib-icon.png"));
}
