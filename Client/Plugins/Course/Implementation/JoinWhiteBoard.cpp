#include	"JoinWhiteBoard.h"

#include	<QSortFilterProxyModel>

#include	"WhiteBoardModel.h"

JoinWhiteBoard::JoinWhiteBoard(PluginManager *pluginManager) : QWidget()
{
	this->ui.setupUi(this);
	QAbstractItemModel		*model = new WhiteBoardModel(pluginManager);
    QSortFilterProxyModel	*proxyModel = new QSortFilterProxyModel(this);
	proxyModel->setFilterRegExp(QRegExp("\\b(ROOT|CLASSES|GRADE|SUBJECT)\\b", Qt::CaseSensitive, QRegExp::RegExp));
	proxyModel->setFilterKeyColumn(1);
	proxyModel->setSourceModel(model);
	this->ui.treeView->setModel(proxyModel);
}
