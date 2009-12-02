/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include		"DragingWidget.h"

#include		<QMouseEvent>
#include		<QDrag>
#include		<QMimeData>
#include		<QApplication>
#include		<QLabel>
#include		<QBoxLayout>

DragingWidget::DragingWidget(QWidget *parent, SmallDisplayablePlugin *plugin) : QFrame(parent)
{
	QBoxLayout	*mainLayout;
	QBoxLayout	*topLayout;
	QBoxLayout	*contentLayout;
	QLabel		*picture;
	QWidget		*content;

	_plugin = plugin;
	setAcceptDrops(true);
	mainLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
	topLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	mainLayout->addLayout(topLayout, 0);
	mainLayout->setMargin(0);
	content = new QFrame(this);
	content->setObjectName("Content");
	contentLayout = new QBoxLayout(QBoxLayout::TopToBottom, content);
	contentLayout->addWidget(plugin->getWidget(), 1);
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
