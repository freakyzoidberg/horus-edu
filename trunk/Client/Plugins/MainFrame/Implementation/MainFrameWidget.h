#ifndef				__MAINFRAMEWIDGET_H__
# define			__MAINFRAMEWIDGET_H__

# include			<QWidget>
# include			<QBoxLayout>
# include			<QLabel>

#include			"../../../Common/PluginManager.h"

class MainFrameWidget : public QWidget
{
    Q_OBJECT

public:
    MainFrameWidget(PluginManager *pluginManager);

private:
    QBoxLayout		*leftLayout;
    QBoxLayout		*rightLayout;
    QLabel*			connectedAs;
    QLabel*			lastLogin;
	PluginManager	*_pluginManager;
	void			fillWidgets();
	void			setStyle();

private slots:
    void			updateInfos();
};

#endif //			__MAINFRAMEWIDGET_H__
