#include	"JoinWhiteBoard.h"

#include	"WhiteBoardModel.h"

JoinWhiteBoard::JoinWhiteBoard(PluginManager *pluginManager) : QWidget()
{
	this->ui.setupUi(this);
	this->ui.treeView->setModel(new WhiteBoardModel(pluginManager));
}
