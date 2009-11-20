#include <QLabel>
#include <QVariant>

#include "classlist.h"

ClassList::ClassList()
{
	  _listLayout = new QVBoxLayout(this);

	  _listLayout->setMargin(0);
	  _listLayout->setSpacing(0);

	  _classList = new QListWidget();

	   QLabel *title = new QLabel(tr("Select a class to view informations."));
	   title->setProperty("isTitle", QVariant(true));
	   _listLayout->addWidget(title);
	   _listLayout->addWidget(_classList);
}
