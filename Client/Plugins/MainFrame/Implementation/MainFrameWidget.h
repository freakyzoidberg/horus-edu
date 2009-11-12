#ifndef				__MAINFRAMEWIDGET_H__
# define			__MAINFRAMEWIDGET_H__

# include			<QWidget>
# include			<QBoxLayout>
# include			<QLabel>
# include			<QComboBox>

#include			"../../../Common/PluginManager.h"

class MainFrameWidget : public QWidget
{
    Q_OBJECT

public:
    MainFrameWidget(PluginManager *pluginManager);
	void			dragEnterEvent(QDragEnterEvent *dragEvent);
	void			dropEvent(QDropEvent *dropEvent);
	void			mouseMoveEvent(QMouseEvent *mouseEvent);

private:
	QComboBox		*stuff;
    QBoxLayout		*leftLayout;
    QBoxLayout		*rightLayout;
    QLabel*			connectedAs;
    QLabel*			lastLogin;
	QWidget			*empty;
	QWidget			*toDelete;
	PluginManager	*_pluginManager;
	void			fillWidgets();
	void			setStyle();
	void			updateSettings();
	void			repopulateStuff();

private slots:
    void			updateInfos();
	void			addedStuff(int index);
};

#endif //			__MAINFRAMEWIDGET_H__
