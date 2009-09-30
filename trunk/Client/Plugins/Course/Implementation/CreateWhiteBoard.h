#ifndef				__CREATEWHITEBOARD_H__
# define			__CREATEWHITEBOARD_H__

# include			<QWidget>

# include			"../../../../Common/PluginManager.h"
# include			"../../../../Common/DataImplementations/WhiteBoardData/WhiteBoardData.h"
# include			"../ui_CreateWhiteBoard.h"

class				CreateWhiteBoard : public QWidget
{
	Q_OBJECT

public:
	CreateWhiteBoard(QWidget *parent, PluginManager *pluginManager);

private:
	Ui::CreateForm	ui;
	PluginManager	*_pluginManager;

private slots:
	void			buttonClicked();

signals:
	void			whiteBoardCreated(WhiteBoardData *whiteBoard);
};

#endif //			__CREATEWHITEBOARD_H__