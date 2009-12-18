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
#include "ImageController.h"

#include <QLabel>
#include <QPixmap>
#include <QFileDialog>
#include <QPushButton>

const QString    ImageController::pluginName() const
{
    return ("imageController");
}

const QString    ImageController::pluginVersion() const
{
    return ("0.2");
}

const QString      ImageController::getSupportedType() const
{
    return ("image");
}

QWidget*            ImageController::createDocumentWidget(ILessonDocument *document, QWidget *loadicon)
{
	int fileId = document->getParameters().value("id").toInt();
	FileData* data = pluginManager->findPlugin<FileDataPlugin*>()->file(fileId);
	return new ImageWidget(data, loadicon);
}

QWidget        *ImageController::editDocument(QFile *, ILessonDocument *)
{
    return 0;
}

QIcon		ImageController::getIcon()
{
	return QIcon(":/image-icon.png");
}

ImageWidget::ImageWidget(FileData *fileData, QWidget* loadicon) : _fileData(fileData), _loadicon(loadicon)
{
	_layout = new QGridLayout();
	_layout->setSpacing(0);
	_layout->setMargin(0);
	setLayout(_layout);
	_layout->addWidget(loadicon);
	loadicon->startTimer(100);
	setStyleSheet("QFrame { background-color: rgb(236, 233, 216); }");
	if (fileData->isDownloaded() || fileData->status() == Data::UPTODATE)
	{
		downloaded();
	}
	else
	{
		connect(fileData, SIGNAL(downloaded()), this, SLOT(downloaded())); 	
	}
}

void	ImageWidget::downloaded()
{
	delete _loadicon;
	setStyleSheet("QFrame { background-color: rgb(100, 100, 100); }");
	_image = QImage(_fileData->fileName());
	_label = new QLabel();
	_label->setAlignment(Qt::AlignCenter);
	_layout->addWidget(_label);
	if (!_image.isNull())
	{
		_label->setPixmap(QPixmap::fromImage(_image.scaled(size(), Qt::KeepAspectRatio)));
	}
}

void	ImageWidget::resizeEvent(QResizeEvent* event)
{
	if (!_image.isNull())
	{
		_label->setPixmap(QPixmap::fromImage(_image.scaled(size(), Qt::KeepAspectRatio)));
	}
}
