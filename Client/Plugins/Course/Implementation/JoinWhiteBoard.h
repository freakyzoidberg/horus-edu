#ifndef				__JOINWHITEBOARD_H__
# define			__JOINWHITEBOARD_H__

# include			<QWidget>

# include			"../../../../Common/PluginManager.h"
# include			"../../../../Common/DataImplementations/WhiteBoardData/WhiteBoardData.h"
# include			"../ui_JoinWhiteBoard.h"

class				JoinWhiteBoard : public QWidget
{
	Q_OBJECT

public:
	JoinWhiteBoard(QWidget *parent, PluginManager *pluginManager);

private:
	Ui::JoinForm	ui;
	PluginManager	*_pluginManager;

private slots:
	void			buttonClicked();
	void			updateTree();

signals:
	void			whiteBoardJoined(WhiteBoardData *whiteBoard);
};

#endif //			__JOINWHITEBOARD_H__