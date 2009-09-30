#include	"JoinWhiteBoard.h"

#include	<QSortFilterProxyModel>
#include	<QVBoxLayout>

#include	"WhiteBoardModel.h"

JoinWhiteBoard::JoinWhiteBoard(QWidget *parent, PluginManager *pluginManager) : QWidget(parent), _pluginManager(pluginManager)
{
	this->ui.setupUi(this);
	QAbstractItemModel		*model = new WhiteBoardModel(pluginManager);
    QSortFilterProxyModel	*proxyModel = new QSortFilterProxyModel(this);
	proxyModel->setFilterRegExp(QRegExp("\\b(ROOT|CLASSES|GRADE|SUBJECT)\\b", Qt::CaseSensitive, QRegExp::RegExp));
	proxyModel->setFilterKeyColumn(1);
	proxyModel->setSourceModel(model);
	this->ui.treeView->setModel(proxyModel);
	connect(this->ui.button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}

void		JoinWhiteBoard::buttonClicked()
{
	emit whiteBoardJoined(_pluginManager->findPlugin<WhiteBoardDataPlugin *>()->getWhiteBoard((quint32) 0));
}