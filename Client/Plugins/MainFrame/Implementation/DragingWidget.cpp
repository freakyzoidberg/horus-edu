#include		"DragingWidget.h"

#include		<QMouseEvent>
#include		<QDrag>
#include		<QMimeData>
#include		<QApplication>
#include		<QLabel>
#include		<QBoxLayout>
#include		<QScrollArea>

DragingWidget::DragingWidget(QWidget *parent, SmallDisplayablePlugin *plugin) : QFrame(parent)
{
	QBoxLayout	*mainLayout;
	QBoxLayout	*topLayout;
	QBoxLayout	*contentLayout;
	QLabel		*picture;
	QScrollArea	*content;

	_plugin = plugin;
	mainLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
	topLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	mainLayout->addLayout(topLayout, 0);
	mainLayout->setMargin(0);
	content = new QScrollArea(this);
	content->setObjectName("Content");
	contentLayout = new QBoxLayout(QBoxLayout::TopToBottom, content);
	//contentLayout->addWidget(plugin->getWidget(), 1);
	content->setWidget(plugin->getWidget());
	mainLayout->addWidget(content, 1);
	picture = new QLabel(this);
	picture->setPixmap(plugin->getIcon().pixmap(20));
	topLayout->addWidget(picture, 0);
	topLayout->addWidget(new QLabel(plugin->getDisplayableName(), this), 1);
	//topLayout->addWidget(new QLabel("Close IMG", this), 0, Qt::AlignRight);
}

void			DragingWidget::mousePressEvent(QMouseEvent *mouseEvent)
{
	if (mouseEvent->button() == Qt::LeftButton )
		startDragPosition = mouseEvent->pos();
}

void			DragingWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{
	QDrag		*drag;
	QMimeData	*mimeData;

	if (!mouseEvent->buttons() & Qt::LeftButton )
		return ;
	if ((mouseEvent->pos() - startDragPosition).manhattanLength() < QApplication::startDragDistance())
		return ;
	mimeData = new QMimeData;
	mimeData->setData("application/vnd.horus.whiteboard.widget", QByteArray(_plugin->pluginName().toAscii()));
	drag = new QDrag(this);
	drag->setPixmap(QPixmap::grabWidget(this));
	drag->setMimeData(mimeData);
	drag->setHotSpot(mouseEvent->pos());
	drag->exec();
}
