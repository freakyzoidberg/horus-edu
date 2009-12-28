#ifndef MARKSMAINVIEW_H
#define MARKSMAINVIEW_H

#include <QTabWidget>

#include "subjectlist.h"
#include "MarksManager.h"
# include	"../../../../Common/PluginManager.h"

class MarksMainView : public QTabWidget
{
public:
					MarksMainView(PluginManager *pluginManager);

private:
	SubjectList		*_subjectList;
	MarksManager	*_marksManager;
};

#endif // MARKSMAINVIEW_H
