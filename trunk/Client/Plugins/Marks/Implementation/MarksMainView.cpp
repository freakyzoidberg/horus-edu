#include "MarksMainView.h"

MarksMainView::MarksMainView(PluginManager *pluginManager)
{
	_subjectList = new SubjectList(pluginManager);

	this->addTab(_subjectList, "Testing...");
}
