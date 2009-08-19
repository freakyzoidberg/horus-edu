#ifndef __PDFEDITOR_H__
# define __PDFEDITOR_H__

# include <QStringList>
# include <QWidget>
# include <QObject>
# include <QDomNode>

# include "../../../../Common/Plugin.h"

# include "TreeWidgetItem.h"

class PdfEditor : public Plugin
{
	Q_OBJECT
	Q_INTERFACES(Plugin)

public:
	const QString	pluginName() const;
	const QString	pluginVersion() const;
	QWidget *getTocInWidget();
	void    buildTocWidget(QDomNode *, TreeWidgetItem *);

private:
	QTreeWidget     *tree;
};

#endif // __PDFEDITOR_H__
