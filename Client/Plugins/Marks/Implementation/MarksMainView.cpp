#include "MarksMainView.h"
#include "../../../../Common/PluginManager.h"
#include "../../../../Common/UserData.h"

MarksMainView::MarksMainView(PluginManager *pluginManager)
{
	_subjectList = new SubjectList(pluginManager);
	this->addTab(_subjectList, QIcon(":/marks.png"), "Testing...");

	if (pluginManager->currentUser()->level() <= LEVEL_TEACHER)
	{
		_marksManager = new MarksManager(pluginManager);
		this->addTab(_marksManager, QIcon(":/marks.png"), tr("Students' grades"));
		this->setTabEnabled(0, false);
	}
}
