#ifndef				__JOINWHITEBOARD_H__
# define			__JOINWHITEBOARD_H__

# include			<QWidget>

# include			"../../../../Common/PluginManager.h"
# include			"../ui_JoinWhiteBoard.h"

class				JoinWhiteBoard : public QWidget
{
public:
	JoinWhiteBoard(PluginManager *pluginManager);

private:
	Ui::JoinForm	ui;
};

#endif //			__JOINWHITEBOARD_H__