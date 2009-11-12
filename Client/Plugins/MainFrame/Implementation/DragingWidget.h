#ifndef						__DRAGINGWIDGET_H__
# define					__DRAGINGWIDGET_H__

# include					<QFrame>
# include					<QPoint>

# include					"../SmallDisplayablePlugin.h"

class						DragingWidget : public QFrame
{
	Q_OBJECT

public:
	DragingWidget(QWidget *parent, SmallDisplayablePlugin *plugin);
	void					mousePressEvent(QMouseEvent *mouseEvent);
	void					mouseMoveEvent(QMouseEvent *mouseEvent);
	SmallDisplayablePlugin	*_plugin;

private:
	QPoint					startDragPosition;
};

#endif
