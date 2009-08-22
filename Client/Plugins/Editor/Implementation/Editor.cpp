#include		"Editor.h"

const QString	Editor::pluginName() const
{
	return ("Editor");
}

const QString	Editor::pluginVersion() const
{
	return ("0.1");
}

QWidget			*Editor::getWidget()
{
	return (0);
}
