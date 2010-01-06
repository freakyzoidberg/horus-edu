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
#ifndef LESSON_H
#define LESSON_H

#include <QXmlDefaultHandler>
#include <QIcon>

#include "../ILessonData.h"
#include "../ILesson.h"
#include "../../../../Common/PluginManager.h"

class Lesson : public ILesson, virtual public QXmlDefaultHandler
{
    Q_OBJECT

public:
	static Lesson* createLesson(FileData *, PluginManager *);

    QVariant data(int column, int role) const;

    bool    startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
    bool    endElement(const QString &namespaceURI, const QString &localName, const QString &qName);
    bool    characters(const QString& ch);

	inline int getId() { return _fileData->id(); }

	FileData *getFiledata() { return _fileData; }

private:
	Lesson(FileData *parent);
    QFile *xmlFile;
    ILessonData *_currentData;
	FileData *_fileData;
	static QIcon *icon;
	static QHash<FileData *, Lesson *> lessons;
	static QHash<QString, QIcon> docIcons;
};

#endif // LESSON_H
