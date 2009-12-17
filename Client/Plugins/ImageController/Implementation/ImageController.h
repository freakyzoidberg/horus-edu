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
#ifndef __IMAGECONTROLLER_H__
# define __IMAGECONTROLLER_H__

# include <QtPlugin>

# include <QLabel>
# include <QImage>
# include <QGridLayout>

# include "../../../../Common/Plugin.h"
# include "../../LessonManager/IDocumentController.h"
# include "../../LessonManager/ILessonManager.h"
# include "../../LessonManager/IDocumentController.h"

class ImageController : public Plugin, public IDocumentController
{
    Q_OBJECT
    Q_INTERFACES(Plugin)
    Q_INTERFACES(IDocumentController)

public:
	const QString		pluginName() const;
	const QString		pluginVersion() const;
    const QString		getSupportedType() const;
    QWidget*			createDocumentWidget(ILessonDocument *document, QWidget *loadicon = NULL);
    QWidget             *editDocument(QFile *metadata, ILessonDocument *);
	QIcon			getIcon();
};

class ImageWidget : public QFrame
{
    Q_OBJECT

public:
	ImageWidget(FileData *fileData, QWidget* loadicon);

public slots:
	void	downloaded();

protected:
	void	resizeEvent(QResizeEvent* event);

private:
	QGridLayout*			_layout;
	FileData*				_fileData;
	QLabel*					_label;
	QWidget*				_loadicon;
	QImage					_image;
};

#endif // __IMAGECONTROLLER_H__
