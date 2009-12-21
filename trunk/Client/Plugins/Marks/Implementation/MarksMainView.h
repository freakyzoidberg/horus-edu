#ifndef MARKSMAINVIEW_H
#define MARKSMAINVIEW_H

#include <QTabWidget>

#include "subjectlist.h"
# include	"../../../../Common/PluginManager.h"

class MarksMainView : public QTabWidget
{
public:
					MarksMainView(PluginManager *pluginManager);

private:
	SubjectList		*_subjectList;
};

#endif // MARKSMAINVIEW_H
